#ifndef BD_AUDIO_H
#define BD_AUDIO_H

	typedef enum levelID LevelID;

	enum specialEffects {
		AUDIO_SFX_DIAMOND_CREATED,
		AUDIO_SFX_DIAMOND_PICK,
		AUDIO_SFX_STEP_DIRT,
		AUDIO_SFX_GATE_OPEN,
		AUDIO_SFX_STONE_FALL,
		AUDIO_SFX_DIAMOND_FELL,
		AUDIO_SFX_STONE_FELL,
		AUDIO_SFX_FOE_KILL,
		AUDIO_SFX_LIFE_UP,
		AUDIO_SFX_LEVEL_WIN,
		AUDIO_SFX_LEVEL_LOSE,
		AUDIO_SFX_START_SCREEN,
		AUDIO_SFX_LEVEL_SCREEN,
		AUDIO_SFX_SCREEN_SELECT,
		AUDIO_SFX_LEVEL_SCREEN_MOVE,
		AUDIO_SFX_GAME_WIN,
		AUDIO_SFX_GAME_LOSE,
		AUDIO_SFX_COUNT
	};

	typedef enum musicRythm {
		RYTHM_ORIGINAL,
		RYTHM_INCREASED_10,
		RYTHM_INCREASED_30,
		RYTHM_INCREASED_60,
		RYTHM_COUNT
	}MusicRythm;

	typedef struct music {
		Mix_Chunk *chunk[RYTHM_COUNT];
		int channel;
		MusicRythm rythm;
	}Music;

	typedef struct sfx {
		Mix_Chunk *chunk;
		int channel;
	}SFX;

	typedef struct audio {
		int allocated_channels;
		SDL_AudioSpec spec;
		Music music[10];
		SFX sfx[AUDIO_SFX_COUNT];
		Uint8 vol_music, vol_sfx;
		int fake_volume_music, fake_volume_sfx;
		int old_fake_volume_music, old_fake_volume_sfx;
		bool mute;
	}Audio;

	void close_audio(void);
	void free_chunk(Mix_Chunk **chunk);
	void free_SFXs(SFX *sfx);
	void free_chunk_musics(Music *music);
	void free_sounds(Audio *audio);
	void free_audio(Audio *audio);
	void change_volume_sounds(Audio *const audio);
	void convert_fake_volume_real(Audio *const audio, GuiVolume changed);
	void set_chunk_volume(Mix_Chunk *chunk, const Uint8 vol);
	void change_music(Mix_Chunk *chunk, const int channel, const int loops, const Uint8 volume);
	void increase_rythm(Music *music, const LevelID levelID, const Uint8 volume);
	void increase_music_speed(Audio *audio, const double rate);
	void play_chunk_fade_timed(Mix_Chunk *chunk, const int channel, const int loops, const int ms, const int ticks);
	void play_chunk_timed(Mix_Chunk *chunk, const int channel, const int loops, const int ticks);
	void play_chunk(Mix_Chunk *chunk, int channel, int loops);
	char* get_sfx_location(const int id);
	Mix_Chunk* get_chunk(char *f_location);
	void load_chunk_musics(Music *music);
	void load_SFXs(SFX *sfx);
	void load_sounds(Audio *audio);
	void open_audio(const SDL_AudioSpec *const spec);
	void init_audio(Audio *audio);

#endif