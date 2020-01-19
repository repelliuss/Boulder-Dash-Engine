#include <RPS/BD.h>

void init_audio(Audio *audio) {

	int id, rythm;
	
	audio->allocated_channels = AUDIO_SFX_COUNT + LEVEL_COUNT * 3 + 1;
	audio->spec.freq = 44100;
	audio->spec.format = AUDIO_S16SYS;
	audio->spec.samples = 4096;
	audio->spec.channels = 2;

	audio->mute = FALSE;
	audio->vol_music = 128;
	audio->vol_sfx = 128;
	audio->fake_volume_music = 100;
	audio->fake_volume_sfx = 100;
	audio->old_fake_volume_music = 100;
	audio->old_fake_volume_sfx = 100;

	for(id = 0; id < LEVEL_COUNT; ++id) {
		for(rythm = 0; rythm < RYTHM_COUNT; ++rythm) {
			audio->music[id].chunk[rythm] = NULL;
		}
		audio->music[id].channel = 0;	/*channel 0 reserved for playing background music*/
		audio->music[id].rythm = RYTHM_ORIGINAL;
	}

	for(id = 0; id < AUDIO_SFX_COUNT; ++id) {
		audio->sfx[id].chunk = NULL;
		audio->sfx[id].channel = id + 1;
	}

}

void open_audio(const SDL_AudioSpec *const spec) {

	if(Mix_OpenAudio(spec->freq, spec->format, spec->channels, spec->samples) < 0) {
		show_mix_error();
	}
}

void load_sounds(Audio *audio) {

	load_chunk_musics(audio->music);
	load_SFXs(audio->sfx);
}

void load_chunk_musics(Music *music) {

	char *f_location = NULL;
	int id;
	MusicRythm rythm;

	for(id = 0; id < LEVEL_COUNT; ++id) {
		for(rythm = RYTHM_ORIGINAL; rythm < RYTHM_COUNT; ++rythm) {
			f_location = get_level_music(rythm, id);
			music[id].chunk[rythm] = get_chunk(f_location);
			free(f_location);
		}
	}

}


void load_SFXs(SFX *sfx) {

	char *f_location;
	int id;

	for(id = 0; id < AUDIO_SFX_COUNT; ++id) {
		f_location = get_sfx_location(id);
		sfx[id].chunk = get_chunk(f_location);
		sfx[id].channel = id + 1;
		free(f_location);
	}
}

void play_chunk(Mix_Chunk *chunk, int channel, int loops) {

	Mix_PlayChannel(channel, chunk, loops);
}

void play_chunk_timed(Mix_Chunk *chunk, const int channel, const int loops, const int ticks) {

	Mix_PlayChannelTimed(channel, chunk, loops, ticks);
}

void play_chunk_fade_timed(Mix_Chunk *chunk, const int channel, const int loops, const int ms, const int ticks) {

	Mix_FadeInChannelTimed(channel, chunk, loops, ms, ticks);
}

Mix_Chunk* get_chunk(char *f_location) {

	Mix_Chunk *chunk = NULL;

	if(f_location != NULL) {
		chunk = Mix_LoadWAV(f_location);
		if(chunk == NULL) {
			printf("Error loading this chunk file: %s\n", f_location);
			show_mix_error();
		}
	}

	return chunk;
}

char* get_sfx_location(const int id) {

	char *str = NULL;

	switch(id) {
		case AUDIO_SFX_DIAMOND_CREATED:
			str = (char*)malloc(34 * sizeof(char));
			copy_string("Resources/SFX/diamond_created.wav", str, 33);
			break;
		case AUDIO_SFX_DIAMOND_PICK:
			str = (char*)malloc(31 * sizeof(char));
			copy_string("Resources/SFX/diamond_pick.wav", str, 30);
			break;
		case AUDIO_SFX_STEP_DIRT:
			str = (char*)malloc(28 * sizeof(char));
			copy_string("Resources/SFX/step_dirt.wav", str, 27);
			break;
		case AUDIO_SFX_GATE_OPEN:
			str = (char*)malloc(28 * sizeof(char));
			copy_string("Resources/SFX/gate_open.wav", str, 27);
			break;
		case AUDIO_SFX_STONE_FALL:
			str = (char*)malloc(29 * sizeof(char));
			copy_string("Resources/SFX/stone_fall.wav", str, 28);
			break;
		case AUDIO_SFX_STONE_FELL:
			str = (char*)malloc(29 * sizeof(char));
			copy_string("Resources/SFX/stone_fell.wav", str, 28);
			break;
		case AUDIO_SFX_DIAMOND_FELL:
			str = (char*)malloc(31 * sizeof(char));
			copy_string("Resources/SFX/diamond_fell.wav", str, 30);
			break;
		case AUDIO_SFX_FOE_KILL:
			str = (char*)malloc(27 * sizeof(char));
			copy_string("Resources/SFX/foe_kill.wav", str, 26);
			break;
		case AUDIO_SFX_LIFE_UP:
			str = (char*)malloc(26 * sizeof(char));
			copy_string("Resources/SFX/life_up.wav", str, 25);
			break;
		case AUDIO_SFX_LEVEL_WIN:
			str = (char*)malloc(28 * sizeof(char));
			copy_string("Resources/SFX/level_win.wav", str, 27);
			break;
		case AUDIO_SFX_LEVEL_LOSE:
			str = (char*)malloc(29 * sizeof(char));
			copy_string("Resources/SFX/level_lose.wav", str, 28);
			break;
		case AUDIO_SFX_START_SCREEN:
			str = (char*)malloc(34 * sizeof(char));
			copy_string("Resources/Musics/title_screen.wav", str, 33);
			break;
		case AUDIO_SFX_LEVEL_SCREEN:
			str = (char*)malloc(25 * sizeof(char));
			copy_string("Resources/Musics/map.wav", str, 24);
			break;
		case AUDIO_SFX_SCREEN_SELECT:
			str = (char*)malloc(32 * sizeof(char));
			copy_string("Resources/SFX/screen_select.wav", str, 31);
			break;
		case AUDIO_SFX_LEVEL_SCREEN_MOVE:
			str = (char*)malloc(36 * sizeof(char));
			copy_string("Resources/SFX/level_screen_move.wav", str, 35);
			break;
		case AUDIO_SFX_GAME_WIN:
			str = (char*)malloc(27 * sizeof(char));
			copy_string("Resources/SFX/game_win.wav", str, 26);
			break;
		case AUDIO_SFX_GAME_LOSE:
			str = (char*)malloc(28 * sizeof(char));
			copy_string("Resources/SFX/game_lose.wav", str, 27);
			break;
		default:
			break;
	}

	return str;
}

void increase_rythm(Music *music, const LevelID levelID, const Uint8 volume) {

	++(music[levelID].rythm);
	change_music(music[levelID].chunk[music[levelID].rythm], music[levelID].channel, -1, volume);
}

void change_music(Mix_Chunk *chunk, const int channel, const int loops, const Uint8 volume) {

	Mix_HaltChannel(channel);
	play_chunk(chunk, channel, loops);
	set_chunk_volume(chunk, volume);
}

/*this function doesn't work right now, will be explained*/
/*void increase_music_speed(Audio *audio, const double rate) {

	SDL_AudioSpec spec;

	spec = audio->music.spec;
	spec.freq = audio->music.spec.freq + (audio->music.spec.freq * rate);

	free_SFXs(audio->sfx);
	
	close_audio();

	open_audio(&spec);

	load_SFXs(audio->sfx);

	Mix_AllocateChannels(audio->allocated_channels);

	play_chunk(audio->music.chunk, audio->music.channel, -1);
}*/

void set_chunk_volume(Mix_Chunk *chunk, const Uint8 vol) {

	chunk->volume = vol;
}

void convert_fake_volume_real(Audio *const audio, GuiVolume changed) {

	switch(changed) {
		case GUI_VOLUME_MUTE:
			audio->old_fake_volume_music = audio->fake_volume_music;
			audio->old_fake_volume_sfx = audio->fake_volume_sfx;
			audio->fake_volume_music = 0;
			audio->fake_volume_sfx = 0;
			audio->vol_music = 0;
			audio->vol_sfx = 0;
			break;
		case GUI_VOLUME_MUSIC:
			audio->vol_music = (Uint8)((128 * audio->fake_volume_music) / 100.0);
			break;
		case GUI_VOLUME_SFX:
			audio->vol_sfx = (Uint8)((128 * audio->fake_volume_sfx) / 100.0);
			break;
		case GUI_VOLUME_UNMUTE:
			audio->fake_volume_music = audio->old_fake_volume_music;
			audio->fake_volume_sfx = audio->old_fake_volume_sfx;
			convert_fake_volume_real(audio, GUI_VOLUME_MUSIC);
			convert_fake_volume_real(audio, GUI_VOLUME_SFX);
			break;
		default:
			break;
	}
}

void change_volume_sounds(Audio *const audio) {

	int id;
	MusicRythm rythm;

	for(id = 0; id < LEVEL_COUNT; ++id) {
		for(rythm = RYTHM_ORIGINAL; rythm < RYTHM_COUNT; ++rythm) {
			set_chunk_volume(audio->music[id].chunk[rythm], audio->vol_music);
		}
	}

	for(id = 0; id < AUDIO_SFX_COUNT; ++id) {
		set_chunk_volume(audio->sfx[id].chunk, audio->vol_sfx);
	}
}

void free_audio(Audio *audio) {

	Mix_HaltChannel(-1);
	Mix_AllocateChannels(0);
	free_sounds(audio);
	close_audio();
}

void free_sounds(Audio *audio) {

	free_chunk_musics(audio->music);
	free_SFXs(audio->sfx);
}

void free_chunk_musics(Music *music) {

	int id;
	MusicRythm rythm;

	for(id = 0; id < LEVEL_COUNT; ++id) {
		for(rythm = RYTHM_ORIGINAL; rythm < RYTHM_COUNT; ++rythm) {
			free_chunk(&(music[id].chunk[rythm]));
		}
	}
}

void free_SFXs(SFX *sfx) {

	int id;

	for(id = 0; id < AUDIO_SFX_COUNT; ++id) {
		free_chunk(&(sfx[id].chunk));
	}
}

void free_chunk(Mix_Chunk **chunk) {

	if(*chunk != NULL) {
		Mix_FreeChunk(*chunk);
		*chunk = NULL;
	}
}

void close_audio(void) {

	Mix_CloseAudio();
}
