<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __Q6_ASM_H__
#घोषणा __Q6_ASM_H__
#समावेश "q6dsp-common.h"
#समावेश <dt-bindings/sound/qcom,q6यंत्र.h>

/* ASM client callback events */
#घोषणा CMD_PAUSE			0x0001
#घोषणा ASM_CLIENT_EVENT_CMD_PAUSE_DONE		0x1001
#घोषणा CMD_FLUSH				0x0002
#घोषणा ASM_CLIENT_EVENT_CMD_FLUSH_DONE		0x1002
#घोषणा CMD_EOS				0x0003
#घोषणा ASM_CLIENT_EVENT_CMD_EOS_DONE		0x1003
#घोषणा CMD_CLOSE				0x0004
#घोषणा ASM_CLIENT_EVENT_CMD_CLOSE_DONE		0x1004
#घोषणा CMD_OUT_FLUSH				0x0005
#घोषणा ASM_CLIENT_EVENT_CMD_OUT_FLUSH_DONE	0x1005
#घोषणा CMD_SUSPEND				0x0006
#घोषणा ASM_CLIENT_EVENT_CMD_SUSPEND_DONE	0x1006
#घोषणा ASM_CLIENT_EVENT_CMD_RUN_DONE		0x1008
#घोषणा ASM_CLIENT_EVENT_DATA_WRITE_DONE	0x1009
#घोषणा ASM_CLIENT_EVENT_DATA_READ_DONE		0x100a
#घोषणा ASM_WRITE_TOKEN_MASK			GENMASK(15, 0)
#घोषणा ASM_WRITE_TOKEN_LEN_MASK		GENMASK(31, 16)
#घोषणा ASM_WRITE_TOKEN_LEN_SHIFT		16

क्रमागत अणु
	LEGACY_PCM_MODE = 0,
	LOW_LATENCY_PCM_MODE,
	ULTRA_LOW_LATENCY_PCM_MODE,
	ULL_POST_PROCESSING_PCM_MODE,
पूर्ण;

#घोषणा MAX_SESSIONS	8
#घोषणा FORMAT_LINEAR_PCM   0x0000
#घोषणा ASM_LAST_BUFFER_FLAG           BIT(30)

काष्ठा q6यंत्र_flac_cfg अणु
        u32 sample_rate;
        u32 ext_sample_rate;
        u32 min_frame_size;
        u32 max_frame_size;
        u16 stream_info_present;
        u16 min_blk_size;
        u16 max_blk_size;
        u16 ch_cfg;
        u16 sample_size;
        u16 md5_sum;
पूर्ण;

काष्ठा q6यंत्र_wma_cfg अणु
	u32 fmtag;
	u32 num_channels;
	u32 sample_rate;
	u32 bytes_per_sec;
	u32 block_align;
	u32 bits_per_sample;
	u32 channel_mask;
	u32 enc_options;
	u32 adv_enc_options;
	u32 adv_enc_options2;
पूर्ण;

काष्ठा q6यंत्र_alac_cfg अणु
	u32 frame_length;
	u8 compatible_version;
	u8 bit_depth;
	u8 pb;
	u8 mb;
	u8 kb;
	u8 num_channels;
	u16 max_run;
	u32 max_frame_bytes;
	u32 avg_bit_rate;
	u32 sample_rate;
	u32 channel_layout_tag;
पूर्ण;

काष्ठा q6यंत्र_ape_cfg अणु
	u16 compatible_version;
	u16 compression_level;
	u32 क्रमmat_flags;
	u32 blocks_per_frame;
	u32 final_frame_blocks;
	u32 total_frames;
	u16 bits_per_sample;
	u16 num_channels;
	u32 sample_rate;
	u32 seek_table_present;
पूर्ण;

प्रकार व्योम (*q6यंत्र_cb) (uपूर्णांक32_t opcode, uपूर्णांक32_t token,
			  व्योम *payload, व्योम *priv);
काष्ठा audio_client;
काष्ठा audio_client *q6यंत्र_audio_client_alloc(काष्ठा device *dev,
					      q6यंत्र_cb cb, व्योम *priv,
					      पूर्णांक session_id, पूर्णांक perf_mode);
व्योम q6यंत्र_audio_client_मुक्त(काष्ठा audio_client *ac);
पूर्णांक q6यंत्र_ग_लिखो_async(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id, uपूर्णांक32_t len,
		      uपूर्णांक32_t msw_ts, uपूर्णांक32_t lsw_ts, uपूर्णांक32_t wflags);
पूर्णांक q6यंत्र_खोलो_ग_लिखो(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
		     uपूर्णांक32_t क्रमmat, u32 codec_profile,
		     uपूर्णांक16_t bits_per_sample, bool is_gapless);

पूर्णांक q6यंत्र_खोलो_पढ़ो(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
		    uपूर्णांक32_t क्रमmat, uपूर्णांक16_t bits_per_sample);
पूर्णांक q6यंत्र_enc_cfg_blk_pcm_क्रमmat_support(काष्ठा audio_client *ac,
					 uपूर्णांक32_t stream_id, uपूर्णांक32_t rate,
					 uपूर्णांक32_t channels,
					 uपूर्णांक16_t bits_per_sample);

पूर्णांक q6यंत्र_पढ़ो(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id);

पूर्णांक q6यंत्र_media_क्रमmat_block_multi_ch_pcm(काष्ठा audio_client *ac,
					  uपूर्णांक32_t stream_id,
					  uपूर्णांक32_t rate, uपूर्णांक32_t channels,
					  u8 channel_map[PCM_MAX_NUM_CHANNEL],
					  uपूर्णांक16_t bits_per_sample);
पूर्णांक q6यंत्र_stream_media_क्रमmat_block_flac(काष्ठा audio_client *ac,
					 uपूर्णांक32_t stream_id,
					 काष्ठा q6यंत्र_flac_cfg *cfg);
पूर्णांक q6यंत्र_stream_media_क्रमmat_block_wma_v9(काष्ठा audio_client *ac,
					   uपूर्णांक32_t stream_id,
					   काष्ठा q6यंत्र_wma_cfg *cfg);
पूर्णांक q6यंत्र_stream_media_क्रमmat_block_wma_v10(काष्ठा audio_client *ac,
					    uपूर्णांक32_t stream_id,
					    काष्ठा q6यंत्र_wma_cfg *cfg);
पूर्णांक q6यंत्र_stream_media_क्रमmat_block_alac(काष्ठा audio_client *ac,
					 uपूर्णांक32_t stream_id,
					 काष्ठा q6यंत्र_alac_cfg *cfg);
पूर्णांक q6यंत्र_stream_media_क्रमmat_block_ape(काष्ठा audio_client *ac,
					uपूर्णांक32_t stream_id,
					काष्ठा q6यंत्र_ape_cfg *cfg);
पूर्णांक q6यंत्र_run(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id, uपूर्णांक32_t flags,
	      uपूर्णांक32_t msw_ts, uपूर्णांक32_t lsw_ts);
पूर्णांक q6यंत्र_run_noरुको(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
		     uपूर्णांक32_t flags, uपूर्णांक32_t msw_ts, uपूर्णांक32_t lsw_ts);
पूर्णांक q6यंत्र_stream_हटाओ_initial_silence(काष्ठा audio_client *ac,
					uपूर्णांक32_t stream_id,
					uपूर्णांक32_t initial_samples);
पूर्णांक q6यंत्र_stream_हटाओ_trailing_silence(काष्ठा audio_client *ac,
					 uपूर्णांक32_t stream_id,
					 uपूर्णांक32_t trailing_samples);
पूर्णांक q6यंत्र_cmd(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,  पूर्णांक cmd);
पूर्णांक q6यंत्र_cmd_noरुको(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,  पूर्णांक cmd);
पूर्णांक q6यंत्र_get_session_id(काष्ठा audio_client *c);
पूर्णांक q6यंत्र_map_memory_regions(अचिन्हित पूर्णांक dir,
			     काष्ठा audio_client *ac,
			     phys_addr_t phys,
			     माप_प्रकार period_sz, अचिन्हित पूर्णांक periods);
पूर्णांक q6यंत्र_unmap_memory_regions(अचिन्हित पूर्णांक dir, काष्ठा audio_client *ac);
#पूर्ण_अगर /* __Q6_ASM_H__ */
