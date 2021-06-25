<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <linux/soc/qcom/apr.h>
#समावेश <linux/device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kref.h>
#समावेश <linux/of.h>
#समावेश <uapi/sound/asound.h>
#समावेश <uapi/sound/compress_params.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश "q6asm.h"
#समावेश "q6core.h"
#समावेश "q6dsp-errno.h"
#समावेश "q6dsp-common.h"

#घोषणा ASM_STREAM_CMD_CLOSE			0x00010BCD
#घोषणा ASM_STREAM_CMD_FLUSH			0x00010BCE
#घोषणा ASM_SESSION_CMD_PAUSE			0x00010BD3
#घोषणा ASM_DATA_CMD_EOS			0x00010BDB
#घोषणा ASM_DATA_EVENT_RENDERED_EOS		0x00010C1C
#घोषणा ASM_शून्य_POPP_TOPOLOGY			0x00010C68
#घोषणा ASM_STREAM_CMD_FLUSH_READBUFS		0x00010C09
#घोषणा ASM_STREAM_CMD_SET_ENCDEC_PARAM		0x00010C10
#घोषणा ASM_STREAM_POSTPROC_TOPO_ID_NONE	0x00010C68
#घोषणा ASM_CMD_SHARED_MEM_MAP_REGIONS		0x00010D92
#घोषणा ASM_CMDRSP_SHARED_MEM_MAP_REGIONS	0x00010D93
#घोषणा ASM_CMD_SHARED_MEM_UNMAP_REGIONS	0x00010D94
#घोषणा ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2	0x00010D98
#घोषणा ASM_DATA_EVENT_WRITE_DONE_V2		0x00010D99
#घोषणा ASM_PARAM_ID_ENCDEC_ENC_CFG_BLK_V2	0x00010DA3
#घोषणा ASM_SESSION_CMD_RUN_V2			0x00010DAA
#घोषणा ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2	0x00010DA5
#घोषणा ASM_MEDIA_FMT_MP3			0x00010BE9
#घोषणा ASM_MEDIA_FMT_FLAC			0x00010C16
#घोषणा ASM_MEDIA_FMT_WMA_V9			0x00010DA8
#घोषणा ASM_MEDIA_FMT_WMA_V10			0x00010DA7
#घोषणा ASM_DATA_CMD_WRITE_V2			0x00010DAB
#घोषणा ASM_DATA_CMD_READ_V2			0x00010DAC
#घोषणा ASM_SESSION_CMD_SUSPEND			0x00010DEC
#घोषणा ASM_STREAM_CMD_OPEN_WRITE_V3		0x00010DB3
#घोषणा ASM_STREAM_CMD_OPEN_READ_V3                 0x00010DB4
#घोषणा ASM_DATA_EVENT_READ_DONE_V2 0x00010D9A
#घोषणा ASM_STREAM_CMD_OPEN_READWRITE_V2        0x00010D8D
#घोषणा ASM_MEDIA_FMT_ALAC			0x00012f31
#घोषणा ASM_MEDIA_FMT_APE			0x00012f32
#घोषणा ASM_DATA_CMD_REMOVE_INITIAL_SILENCE	0x00010D67
#घोषणा ASM_DATA_CMD_REMOVE_TRAILING_SILENCE	0x00010D68


#घोषणा ASM_LEGACY_STREAM_SESSION	0
/* Bit shअगरt क्रम the stream_perf_mode subfield. */
#घोषणा ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_READ              29
#घोषणा ASM_END_POINT_DEVICE_MATRIX	0
#घोषणा ASM_DEFAULT_APP_TYPE		0
#घोषणा ASM_SYNC_IO_MODE		0x0001
#घोषणा ASM_ASYNC_IO_MODE		0x0002
#घोषणा ASM_TUN_READ_IO_MODE		0x0004	/* tunnel पढ़ो ग_लिखो mode */
#घोषणा ASM_TUN_WRITE_IO_MODE		0x0008	/* tunnel पढ़ो ग_लिखो mode */
#घोषणा ASM_SHIFT_GAPLESS_MODE_FLAG	31
#घोषणा ADSP_MEMORY_MAP_SHMEM8_4K_POOL	3

काष्ठा avs_cmd_shared_mem_map_regions अणु
	u16 mem_pool_id;
	u16 num_regions;
	u32 property_flag;
पूर्ण __packed;

काष्ठा avs_shared_map_region_payload अणु
	u32 shm_addr_lsw;
	u32 shm_addr_msw;
	u32 mem_size_bytes;
पूर्ण __packed;

काष्ठा avs_cmd_shared_mem_unmap_regions अणु
	u32 mem_map_handle;
पूर्ण __packed;

काष्ठा यंत्र_data_cmd_media_fmt_update_v2 अणु
	u32 fmt_blk_size;
पूर्ण __packed;

काष्ठा यंत्र_multi_channel_pcm_fmt_blk_v2 अणु
	काष्ठा यंत्र_data_cmd_media_fmt_update_v2 fmt_blk;
	u16 num_channels;
	u16 bits_per_sample;
	u32 sample_rate;
	u16 is_चिन्हित;
	u16 reserved;
	u8 channel_mapping[PCM_MAX_NUM_CHANNEL];
पूर्ण __packed;

काष्ठा यंत्र_flac_fmt_blk_v2 अणु
	काष्ठा यंत्र_data_cmd_media_fmt_update_v2 fmt_blk;
	u16 is_stream_info_present;
	u16 num_channels;
	u16 min_blk_size;
	u16 max_blk_size;
	u16 md5_sum[8];
	u32 sample_rate;
	u32 min_frame_size;
	u32 max_frame_size;
	u16 sample_size;
	u16 reserved;
पूर्ण __packed;

काष्ठा यंत्र_wmastdv9_fmt_blk_v2 अणु
	काष्ठा यंत्र_data_cmd_media_fmt_update_v2 fmt_blk;
	u16          fmtag;
	u16          num_channels;
	u32          sample_rate;
	u32          bytes_per_sec;
	u16          blk_align;
	u16          bits_per_sample;
	u32          channel_mask;
	u16          enc_options;
	u16          reserved;
पूर्ण __packed;

काष्ठा यंत्र_wmaprov10_fmt_blk_v2 अणु
	काष्ठा यंत्र_data_cmd_media_fmt_update_v2 fmt_blk;
	u16          fmtag;
	u16          num_channels;
	u32          sample_rate;
	u32          bytes_per_sec;
	u16          blk_align;
	u16          bits_per_sample;
	u32          channel_mask;
	u16          enc_options;
	u16          advanced_enc_options1;
	u32          advanced_enc_options2;
पूर्ण __packed;

काष्ठा यंत्र_alac_fmt_blk_v2 अणु
	काष्ठा यंत्र_data_cmd_media_fmt_update_v2 fmt_blk;
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
पूर्ण __packed;

काष्ठा यंत्र_ape_fmt_blk_v2 अणु
	काष्ठा यंत्र_data_cmd_media_fmt_update_v2 fmt_blk;
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
पूर्ण __packed;

काष्ठा यंत्र_stream_cmd_set_encdec_param अणु
	u32                  param_id;
	u32                  param_size;
पूर्ण __packed;

काष्ठा यंत्र_enc_cfg_blk_param_v2 अणु
	u32                  frames_per_buf;
	u32                  enc_cfg_blk_size;
पूर्ण __packed;

काष्ठा यंत्र_multi_channel_pcm_enc_cfg_v2 अणु
	काष्ठा यंत्र_stream_cmd_set_encdec_param  encdec;
	काष्ठा यंत्र_enc_cfg_blk_param_v2	encblk;
	uपूर्णांक16_t  num_channels;
	uपूर्णांक16_t  bits_per_sample;
	uपूर्णांक32_t  sample_rate;
	uपूर्णांक16_t  is_चिन्हित;
	uपूर्णांक16_t  reserved;
	uपूर्णांक8_t   channel_mapping[8];
पूर्ण __packed;

काष्ठा यंत्र_data_cmd_पढ़ो_v2 अणु
	u32                  buf_addr_lsw;
	u32                  buf_addr_msw;
	u32                  mem_map_handle;
	u32                  buf_size;
	u32                  seq_id;
पूर्ण __packed;

काष्ठा यंत्र_data_cmd_पढ़ो_v2_करोne अणु
	u32	status;
	u32	buf_addr_lsw;
	u32	buf_addr_msw;
पूर्ण;

काष्ठा यंत्र_stream_cmd_खोलो_पढ़ो_v3 अणु
	u32                    mode_flags;
	u32                    src_endpoपूर्णांकype;
	u32                    preprocopo_id;
	u32                    enc_cfg_id;
	u16                    bits_per_sample;
	u16                    reserved;
पूर्ण __packed;

काष्ठा यंत्र_data_cmd_ग_लिखो_v2 अणु
	u32 buf_addr_lsw;
	u32 buf_addr_msw;
	u32 mem_map_handle;
	u32 buf_size;
	u32 seq_id;
	u32 बारtamp_lsw;
	u32 बारtamp_msw;
	u32 flags;
पूर्ण __packed;

काष्ठा यंत्र_stream_cmd_खोलो_ग_लिखो_v3 अणु
	uपूर्णांक32_t mode_flags;
	uपूर्णांक16_t sink_endpoपूर्णांकype;
	uपूर्णांक16_t bits_per_sample;
	uपूर्णांक32_t postprocopo_id;
	uपूर्णांक32_t dec_fmt_id;
पूर्ण __packed;

काष्ठा यंत्र_session_cmd_run_v2 अणु
	u32 flags;
	u32 समय_lsw;
	u32 समय_msw;
पूर्ण __packed;

काष्ठा audio_buffer अणु
	phys_addr_t phys;
	uपूर्णांक32_t size;		/* size of buffer */
पूर्ण;

काष्ठा audio_port_data अणु
	काष्ठा audio_buffer *buf;
	uपूर्णांक32_t num_periods;
	uपूर्णांक32_t dsp_buf;
	uपूर्णांक32_t mem_map_handle;
पूर्ण;

काष्ठा q6यंत्र अणु
	काष्ठा apr_device *adev;
	काष्ठा device *dev;
	काष्ठा q6core_svc_api_info ainfo;
	रुको_queue_head_t mem_रुको;
	spinlock_t slock;
	काष्ठा audio_client *session[MAX_SESSIONS + 1];
पूर्ण;

काष्ठा audio_client अणु
	पूर्णांक session;
	q6यंत्र_cb cb;
	व्योम *priv;
	uपूर्णांक32_t io_mode;
	काष्ठा apr_device *adev;
	काष्ठा mutex cmd_lock;
	spinlock_t lock;
	काष्ठा kref refcount;
	/* idx:1 out port, 0: in port */
	काष्ठा audio_port_data port[2];
	रुको_queue_head_t cmd_रुको;
	काष्ठा aprv2_ibasic_rsp_result_t result;
	पूर्णांक perf_mode;
	काष्ठा q6यंत्र *q6यंत्र;
	काष्ठा device *dev;
पूर्ण;

अटल अंतरभूत व्योम q6यंत्र_add_hdr(काष्ठा audio_client *ac, काष्ठा apr_hdr *hdr,
				 uपूर्णांक32_t pkt_size, bool cmd_flg,
				 uपूर्णांक32_t stream_id)
अणु
	hdr->hdr_field = APR_SEQ_CMD_HDR_FIELD;
	hdr->src_port = ((ac->session << 8) & 0xFF00) | (stream_id);
	hdr->dest_port = ((ac->session << 8) & 0xFF00) | (stream_id);
	hdr->pkt_size = pkt_size;
	अगर (cmd_flg)
		hdr->token = ac->session;
पूर्ण

अटल पूर्णांक q6यंत्र_apr_send_session_pkt(काष्ठा q6यंत्र *a, काष्ठा audio_client *ac,
				      काष्ठा apr_pkt *pkt, uपूर्णांक32_t rsp_opcode)
अणु
	काष्ठा apr_hdr *hdr = &pkt->hdr;
	पूर्णांक rc;

	mutex_lock(&ac->cmd_lock);
	ac->result.opcode = 0;
	ac->result.status = 0;
	rc = apr_send_pkt(a->adev, pkt);
	अगर (rc < 0)
		जाओ err;

	अगर (rsp_opcode)
		rc = रुको_event_समयout(a->mem_रुको,
					(ac->result.opcode == hdr->opcode) ||
					(ac->result.opcode == rsp_opcode),
					5 * HZ);
	अन्यथा
		rc = रुको_event_समयout(a->mem_रुको,
					(ac->result.opcode == hdr->opcode),
					5 * HZ);

	अगर (!rc) अणु
		dev_err(a->dev, "CMD %x timeout\n", hdr->opcode);
		rc = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (ac->result.status > 0) अणु
		dev_err(a->dev, "DSP returned error[%x]\n",
			ac->result.status);
		rc = -EINVAL;
	पूर्ण

err:
	mutex_unlock(&ac->cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक __q6यंत्र_memory_unmap(काष्ठा audio_client *ac,
				phys_addr_t buf_add, पूर्णांक dir)
अणु
	काष्ठा avs_cmd_shared_mem_unmap_regions *mem_unmap;
	काष्ठा q6यंत्र *a = dev_get_drvdata(ac->dev->parent);
	काष्ठा apr_pkt *pkt;
	पूर्णांक rc, pkt_size;
	व्योम *p;

	अगर (ac->port[dir].mem_map_handle == 0) अणु
		dev_err(ac->dev, "invalid mem handle\n");
		वापस -EINVAL;
	पूर्ण

	pkt_size = APR_HDR_SIZE + माप(*mem_unmap);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	mem_unmap = p + APR_HDR_SIZE;

	pkt->hdr.hdr_field = APR_SEQ_CMD_HDR_FIELD;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.token = ((ac->session << 8) | dir);

	pkt->hdr.opcode = ASM_CMD_SHARED_MEM_UNMAP_REGIONS;
	mem_unmap->mem_map_handle = ac->port[dir].mem_map_handle;

	rc = q6यंत्र_apr_send_session_pkt(a, ac, pkt, 0);
	अगर (rc < 0) अणु
		kमुक्त(pkt);
		वापस rc;
	पूर्ण

	ac->port[dir].mem_map_handle = 0;

	kमुक्त(pkt);
	वापस 0;
पूर्ण


अटल व्योम q6यंत्र_audio_client_मुक्त_buf(काष्ठा audio_client *ac,
					काष्ठा audio_port_data *port)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ac->lock, flags);
	port->num_periods = 0;
	kमुक्त(port->buf);
	port->buf = शून्य;
	spin_unlock_irqrestore(&ac->lock, flags);
पूर्ण

/**
 * q6यंत्र_unmap_memory_regions() - unmap memory regions in the dsp.
 *
 * @dir: direction of audio stream
 * @ac: audio client instanace
 *
 * Return: Will be an negative value on failure or zero on success
 */
पूर्णांक q6यंत्र_unmap_memory_regions(अचिन्हित पूर्णांक dir, काष्ठा audio_client *ac)
अणु
	काष्ठा audio_port_data *port;
	पूर्णांक cnt = 0;
	पूर्णांक rc = 0;

	port = &ac->port[dir];
	अगर (!port->buf) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	cnt = port->num_periods - 1;
	अगर (cnt >= 0) अणु
		rc = __q6यंत्र_memory_unmap(ac, port->buf[dir].phys, dir);
		अगर (rc < 0) अणु
			dev_err(ac->dev, "%s: Memory_unmap_regions failed %d\n",
				__func__, rc);
			जाओ err;
		पूर्ण
	पूर्ण

	q6यंत्र_audio_client_मुक्त_buf(ac, port);

err:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_unmap_memory_regions);

अटल पूर्णांक __q6यंत्र_memory_map_regions(काष्ठा audio_client *ac, पूर्णांक dir,
				      माप_प्रकार period_sz, अचिन्हित पूर्णांक periods,
				      bool is_contiguous)
अणु
	काष्ठा avs_cmd_shared_mem_map_regions *cmd = शून्य;
	काष्ठा avs_shared_map_region_payload *mregions = शून्य;
	काष्ठा q6यंत्र *a = dev_get_drvdata(ac->dev->parent);
	काष्ठा audio_port_data *port = शून्य;
	काष्ठा audio_buffer *ab = शून्य;
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t num_regions, buf_sz;
	पूर्णांक rc, i, pkt_size;

	अगर (is_contiguous) अणु
		num_regions = 1;
		buf_sz = period_sz * periods;
	पूर्ण अन्यथा अणु
		buf_sz = period_sz;
		num_regions = periods;
	पूर्ण

	/* DSP expects size should be aligned to 4K */
	buf_sz = ALIGN(buf_sz, 4096);

	pkt_size = APR_HDR_SIZE + माप(*cmd) +
		   (माप(*mregions) * num_regions);

	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	cmd = p + APR_HDR_SIZE;
	mregions = p + APR_HDR_SIZE +  माप(*cmd);

	pkt->hdr.hdr_field = APR_SEQ_CMD_HDR_FIELD;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.token = ((ac->session << 8) | dir);
	pkt->hdr.opcode = ASM_CMD_SHARED_MEM_MAP_REGIONS;

	cmd->mem_pool_id = ADSP_MEMORY_MAP_SHMEM8_4K_POOL;
	cmd->num_regions = num_regions;
	cmd->property_flag = 0x00;

	spin_lock_irqsave(&ac->lock, flags);
	port = &ac->port[dir];

	क्रम (i = 0; i < num_regions; i++) अणु
		ab = &port->buf[i];
		mregions->shm_addr_lsw = lower_32_bits(ab->phys);
		mregions->shm_addr_msw = upper_32_bits(ab->phys);
		mregions->mem_size_bytes = buf_sz;
		++mregions;
	पूर्ण
	spin_unlock_irqrestore(&ac->lock, flags);

	rc = q6यंत्र_apr_send_session_pkt(a, ac, pkt,
					ASM_CMDRSP_SHARED_MEM_MAP_REGIONS);

	kमुक्त(pkt);

	वापस rc;
पूर्ण

/**
 * q6यंत्र_map_memory_regions() - map memory regions in the dsp.
 *
 * @dir: direction of audio stream
 * @ac: audio client instanace
 * @phys: physical address that needs mapping.
 * @period_sz: audio period size
 * @periods: number of periods
 *
 * Return: Will be an negative value on failure or zero on success
 */
पूर्णांक q6यंत्र_map_memory_regions(अचिन्हित पूर्णांक dir, काष्ठा audio_client *ac,
			     phys_addr_t phys,
			     माप_प्रकार period_sz, अचिन्हित पूर्णांक periods)
अणु
	काष्ठा audio_buffer *buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक cnt;
	पूर्णांक rc;

	spin_lock_irqsave(&ac->lock, flags);
	अगर (ac->port[dir].buf) अणु
		dev_err(ac->dev, "Buffer already allocated\n");
		spin_unlock_irqrestore(&ac->lock, flags);
		वापस 0;
	पूर्ण

	buf = kzalloc(((माप(काष्ठा audio_buffer)) * periods), GFP_ATOMIC);
	अगर (!buf) अणु
		spin_unlock_irqrestore(&ac->lock, flags);
		वापस -ENOMEM;
	पूर्ण


	ac->port[dir].buf = buf;

	buf[0].phys = phys;
	buf[0].size = period_sz;

	क्रम (cnt = 1; cnt < periods; cnt++) अणु
		अगर (period_sz > 0) अणु
			buf[cnt].phys = buf[0].phys + (cnt * period_sz);
			buf[cnt].size = period_sz;
		पूर्ण
	पूर्ण
	ac->port[dir].num_periods = periods;

	spin_unlock_irqrestore(&ac->lock, flags);

	rc = __q6यंत्र_memory_map_regions(ac, dir, period_sz, periods, 1);
	अगर (rc < 0) अणु
		dev_err(ac->dev, "Memory_map_regions failed\n");
		q6यंत्र_audio_client_मुक्त_buf(ac, &ac->port[dir]);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_map_memory_regions);

अटल व्योम q6यंत्र_audio_client_release(काष्ठा kref *ref)
अणु
	काष्ठा audio_client *ac;
	काष्ठा q6यंत्र *a;
	अचिन्हित दीर्घ flags;

	ac = container_of(ref, काष्ठा audio_client, refcount);
	a = ac->q6यंत्र;

	spin_lock_irqsave(&a->slock, flags);
	a->session[ac->session] = शून्य;
	spin_unlock_irqrestore(&a->slock, flags);

	kमुक्त(ac);
पूर्ण

/**
 * q6यंत्र_audio_client_मुक्त() - Freee allocated audio client
 *
 * @ac: audio client to मुक्त
 */
व्योम q6यंत्र_audio_client_मुक्त(काष्ठा audio_client *ac)
अणु
	kref_put(&ac->refcount, q6यंत्र_audio_client_release);
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_audio_client_मुक्त);

अटल काष्ठा audio_client *q6यंत्र_get_audio_client(काष्ठा q6यंत्र *a,
						   पूर्णांक session_id)
अणु
	काष्ठा audio_client *ac = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&a->slock, flags);
	अगर ((session_id <= 0) || (session_id > MAX_SESSIONS)) अणु
		dev_err(a->dev, "invalid session: %d\n", session_id);
		जाओ err;
	पूर्ण

	/* check क्रम valid session */
	अगर (!a->session[session_id])
		जाओ err;
	अन्यथा अगर (a->session[session_id]->session != session_id)
		जाओ err;

	ac = a->session[session_id];
	kref_get(&ac->refcount);
err:
	spin_unlock_irqrestore(&a->slock, flags);
	वापस ac;
पूर्ण

अटल पूर्णांक32_t q6यंत्र_stream_callback(काष्ठा apr_device *adev,
				     काष्ठा apr_resp_pkt *data,
				     पूर्णांक session_id)
अणु
	काष्ठा q6यंत्र *q6यंत्र = dev_get_drvdata(&adev->dev);
	काष्ठा aprv2_ibasic_rsp_result_t *result;
	काष्ठा apr_hdr *hdr = &data->hdr;
	काष्ठा audio_port_data *port;
	काष्ठा audio_client *ac;
	uपूर्णांक32_t client_event = 0;
	पूर्णांक ret = 0;

	ac = q6यंत्र_get_audio_client(q6यंत्र, session_id);
	अगर (!ac)/* Audio client might alपढ़ोy be मुक्तd by now */
		वापस 0;

	result = data->payload;

	चयन (hdr->opcode) अणु
	हाल APR_BASIC_RSP_RESULT:
		चयन (result->opcode) अणु
		हाल ASM_SESSION_CMD_PAUSE:
			client_event = ASM_CLIENT_EVENT_CMD_PAUSE_DONE;
			अवरोध;
		हाल ASM_SESSION_CMD_SUSPEND:
			client_event = ASM_CLIENT_EVENT_CMD_SUSPEND_DONE;
			अवरोध;
		हाल ASM_STREAM_CMD_FLUSH:
			client_event = ASM_CLIENT_EVENT_CMD_FLUSH_DONE;
			अवरोध;
		हाल ASM_SESSION_CMD_RUN_V2:
			client_event = ASM_CLIENT_EVENT_CMD_RUN_DONE;
			अवरोध;
		हाल ASM_STREAM_CMD_CLOSE:
			client_event = ASM_CLIENT_EVENT_CMD_CLOSE_DONE;
			अवरोध;
		हाल ASM_STREAM_CMD_FLUSH_READBUFS:
			client_event = ASM_CLIENT_EVENT_CMD_OUT_FLUSH_DONE;
			अवरोध;
		हाल ASM_STREAM_CMD_OPEN_WRITE_V3:
		हाल ASM_STREAM_CMD_OPEN_READ_V3:
		हाल ASM_STREAM_CMD_OPEN_READWRITE_V2:
		हाल ASM_STREAM_CMD_SET_ENCDEC_PARAM:
		हाल ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2:
		हाल ASM_DATA_CMD_REMOVE_INITIAL_SILENCE:
		हाल ASM_DATA_CMD_REMOVE_TRAILING_SILENCE:
			अगर (result->status != 0) अणु
				dev_err(ac->dev,
					"cmd = 0x%x returned error = 0x%x\n",
					result->opcode, result->status);
				ac->result = *result;
				wake_up(&ac->cmd_रुको);
				ret = 0;
				जाओ करोne;
			पूर्ण
			अवरोध;
		शेष:
			dev_err(ac->dev, "command[0x%x] not expecting rsp\n",
				result->opcode);
			अवरोध;
		पूर्ण

		ac->result = *result;
		wake_up(&ac->cmd_रुको);

		अगर (ac->cb)
			ac->cb(client_event, hdr->token,
			       data->payload, ac->priv);

		ret = 0;
		जाओ करोne;

	हाल ASM_DATA_EVENT_WRITE_DONE_V2:
		client_event = ASM_CLIENT_EVENT_DATA_WRITE_DONE;
		अगर (ac->io_mode & ASM_SYNC_IO_MODE) अणु
			phys_addr_t phys;
			अचिन्हित दीर्घ flags;
			पूर्णांक token = hdr->token & ASM_WRITE_TOKEN_MASK;

			spin_lock_irqsave(&ac->lock, flags);

			port =  &ac->port[SNDRV_PCM_STREAM_PLAYBACK];

			अगर (!port->buf) अणु
				spin_unlock_irqrestore(&ac->lock, flags);
				ret = 0;
				जाओ करोne;
			पूर्ण

			phys = port->buf[token].phys;

			अगर (lower_32_bits(phys) != result->opcode ||
			    upper_32_bits(phys) != result->status) अणु
				dev_err(ac->dev, "Expected addr %pa\n",
					&port->buf[token].phys);
				spin_unlock_irqrestore(&ac->lock, flags);
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			spin_unlock_irqrestore(&ac->lock, flags);
		पूर्ण
		अवरोध;
	हाल ASM_DATA_EVENT_READ_DONE_V2:
		client_event = ASM_CLIENT_EVENT_DATA_READ_DONE;
		अगर (ac->io_mode & ASM_SYNC_IO_MODE) अणु
			काष्ठा यंत्र_data_cmd_पढ़ो_v2_करोne *करोne = data->payload;
			अचिन्हित दीर्घ flags;
			phys_addr_t phys;

			spin_lock_irqsave(&ac->lock, flags);
			port =  &ac->port[SNDRV_PCM_STREAM_CAPTURE];
			अगर (!port->buf) अणु
				spin_unlock_irqrestore(&ac->lock, flags);
				ret = 0;
				जाओ करोne;
			पूर्ण

			phys = port->buf[hdr->token].phys;

			अगर (upper_32_bits(phys) != करोne->buf_addr_msw ||
			    lower_32_bits(phys) != करोne->buf_addr_lsw) अणु
				dev_err(ac->dev, "Expected addr %pa %08x-%08x\n",
					&port->buf[hdr->token].phys,
					करोne->buf_addr_lsw,
					करोne->buf_addr_msw);
				spin_unlock_irqrestore(&ac->lock, flags);
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			spin_unlock_irqrestore(&ac->lock, flags);
		पूर्ण

		अवरोध;
	हाल ASM_DATA_EVENT_RENDERED_EOS:
		client_event = ASM_CLIENT_EVENT_CMD_EOS_DONE;
		अवरोध;
	पूर्ण

	अगर (ac->cb)
		ac->cb(client_event, hdr->token, data->payload, ac->priv);

करोne:
	kref_put(&ac->refcount, q6यंत्र_audio_client_release);
	वापस ret;
पूर्ण

अटल पूर्णांक q6यंत्र_srvc_callback(काष्ठा apr_device *adev,
			       काष्ठा apr_resp_pkt *data)
अणु
	काष्ठा q6यंत्र *q6यंत्र = dev_get_drvdata(&adev->dev);
	काष्ठा aprv2_ibasic_rsp_result_t *result;
	काष्ठा audio_port_data *port;
	काष्ठा audio_client *ac = शून्य;
	काष्ठा apr_hdr *hdr = &data->hdr;
	काष्ठा q6यंत्र *a;
	uपूर्णांक32_t sid = 0;
	uपूर्णांक32_t dir = 0;
	पूर्णांक session_id;

	session_id = (hdr->dest_port >> 8) & 0xFF;
	अगर (session_id)
		वापस q6यंत्र_stream_callback(adev, data, session_id);

	sid = (hdr->token >> 8) & 0x0F;
	ac = q6यंत्र_get_audio_client(q6यंत्र, sid);
	अगर (!ac) अणु
		dev_err(&adev->dev, "Audio Client not active\n");
		वापस 0;
	पूर्ण

	a = dev_get_drvdata(ac->dev->parent);
	dir = (hdr->token & 0x0F);
	port = &ac->port[dir];
	result = data->payload;

	चयन (hdr->opcode) अणु
	हाल APR_BASIC_RSP_RESULT:
		चयन (result->opcode) अणु
		हाल ASM_CMD_SHARED_MEM_MAP_REGIONS:
		हाल ASM_CMD_SHARED_MEM_UNMAP_REGIONS:
			ac->result = *result;
			wake_up(&a->mem_रुको);
			अवरोध;
		शेष:
			dev_err(&adev->dev, "command[0x%x] not expecting rsp\n",
				 result->opcode);
			अवरोध;
		पूर्ण
		जाओ करोne;
	हाल ASM_CMDRSP_SHARED_MEM_MAP_REGIONS:
		ac->result.status = 0;
		ac->result.opcode = hdr->opcode;
		port->mem_map_handle = result->opcode;
		wake_up(&a->mem_रुको);
		अवरोध;
	हाल ASM_CMD_SHARED_MEM_UNMAP_REGIONS:
		ac->result.opcode = hdr->opcode;
		ac->result.status = 0;
		port->mem_map_handle = 0;
		wake_up(&a->mem_रुको);
		अवरोध;
	शेष:
		dev_dbg(&adev->dev, "command[0x%x]success [0x%x]\n",
			result->opcode, result->status);
		अवरोध;
	पूर्ण

	अगर (ac->cb)
		ac->cb(hdr->opcode, hdr->token, data->payload, ac->priv);

करोne:
	kref_put(&ac->refcount, q6यंत्र_audio_client_release);

	वापस 0;
पूर्ण

/**
 * q6यंत्र_get_session_id() - get session id क्रम audio client
 *
 * @c: audio client poपूर्णांकer
 *
 * Return: Will be an session id of the audio client.
 */
पूर्णांक q6यंत्र_get_session_id(काष्ठा audio_client *c)
अणु
	वापस c->session;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_get_session_id);

/**
 * q6यंत्र_audio_client_alloc() - Allocate a new audio client
 *
 * @dev: Poपूर्णांकer to यंत्र child device.
 * @cb: event callback.
 * @priv: निजी data associated with this client.
 * @session_id: session id
 * @perf_mode: perक्रमmace mode क्रम this client
 *
 * Return: Will be an error poपूर्णांकer on error or a valid audio client
 * on success.
 */
काष्ठा audio_client *q6यंत्र_audio_client_alloc(काष्ठा device *dev, q6यंत्र_cb cb,
					      व्योम *priv, पूर्णांक session_id,
					      पूर्णांक perf_mode)
अणु
	काष्ठा q6यंत्र *a = dev_get_drvdata(dev->parent);
	काष्ठा audio_client *ac;
	अचिन्हित दीर्घ flags;

	ac = q6यंत्र_get_audio_client(a, session_id + 1);
	अगर (ac) अणु
		dev_err(dev, "Audio Client already active\n");
		वापस ac;
	पूर्ण

	ac = kzalloc(माप(*ac), GFP_KERNEL);
	अगर (!ac)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_irqsave(&a->slock, flags);
	a->session[session_id + 1] = ac;
	spin_unlock_irqrestore(&a->slock, flags);
	ac->session = session_id + 1;
	ac->cb = cb;
	ac->dev = dev;
	ac->q6यंत्र = a;
	ac->priv = priv;
	ac->io_mode = ASM_SYNC_IO_MODE;
	ac->perf_mode = perf_mode;
	ac->adev = a->adev;
	kref_init(&ac->refcount);

	init_रुकोqueue_head(&ac->cmd_रुको);
	mutex_init(&ac->cmd_lock);
	spin_lock_init(&ac->lock);

	वापस ac;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_audio_client_alloc);

अटल पूर्णांक q6यंत्र_ac_send_cmd_sync(काष्ठा audio_client *ac, काष्ठा apr_pkt *pkt)
अणु
	काष्ठा apr_hdr *hdr = &pkt->hdr;
	पूर्णांक rc;

	mutex_lock(&ac->cmd_lock);
	ac->result.opcode = 0;
	ac->result.status = 0;

	rc = apr_send_pkt(ac->adev, pkt);
	अगर (rc < 0)
		जाओ err;

	rc = रुको_event_समयout(ac->cmd_रुको,
				(ac->result.opcode == hdr->opcode), 5 * HZ);
	अगर (!rc) अणु
		dev_err(ac->dev, "CMD %x timeout\n", hdr->opcode);
		rc =  -ETIMEDOUT;
		जाओ err;
	पूर्ण

	अगर (ac->result.status > 0) अणु
		dev_err(ac->dev, "DSP returned error[%x]\n",
			ac->result.status);
		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		rc = 0;
	पूर्ण


err:
	mutex_unlock(&ac->cmd_lock);
	वापस rc;
पूर्ण

/**
 * q6यंत्र_खोलो_ग_लिखो() - Open audio client क्रम writing
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id of q6यंत्र session
 * @क्रमmat: audio sample क्रमmat
 * @codec_profile: compressed क्रमmat profile
 * @bits_per_sample: bits per sample
 * @is_gapless: flag to indicate अगर this is a gapless stream
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_खोलो_ग_लिखो(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
		     uपूर्णांक32_t क्रमmat, u32 codec_profile,
		     uपूर्णांक16_t bits_per_sample, bool is_gapless)
अणु
	काष्ठा यंत्र_stream_cmd_खोलो_ग_लिखो_v3 *खोलो;
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	पूर्णांक rc, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(*खोलो);

	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	खोलो = p + APR_HDR_SIZE;
	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_STREAM_CMD_OPEN_WRITE_V3;
	खोलो->mode_flags = 0x00;
	खोलो->mode_flags |= ASM_LEGACY_STREAM_SESSION;
	अगर (is_gapless)
		खोलो->mode_flags |= BIT(ASM_SHIFT_GAPLESS_MODE_FLAG);

	/* source endpoपूर्णांक : matrix */
	खोलो->sink_endpoपूर्णांकype = ASM_END_POINT_DEVICE_MATRIX;
	खोलो->bits_per_sample = bits_per_sample;
	खोलो->postprocopo_id = ASM_शून्य_POPP_TOPOLOGY;

	चयन (क्रमmat) अणु
	हाल SND_AUDIOCODEC_MP3:
		खोलो->dec_fmt_id = ASM_MEDIA_FMT_MP3;
		अवरोध;
	हाल FORMAT_LINEAR_PCM:
		खोलो->dec_fmt_id = ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2;
		अवरोध;
	हाल SND_AUDIOCODEC_FLAC:
		खोलो->dec_fmt_id = ASM_MEDIA_FMT_FLAC;
		अवरोध;
	हाल SND_AUDIOCODEC_WMA:
		चयन (codec_profile) अणु
		हाल SND_AUDIOPROखाता_WMA9:
			खोलो->dec_fmt_id = ASM_MEDIA_FMT_WMA_V9;
			अवरोध;
		हाल SND_AUDIOPROखाता_WMA10:
		हाल SND_AUDIOPROखाता_WMA9_PRO:
		हाल SND_AUDIOPROखाता_WMA9_LOSSLESS:
		हाल SND_AUDIOPROखाता_WMA10_LOSSLESS:
			खोलो->dec_fmt_id = ASM_MEDIA_FMT_WMA_V10;
			अवरोध;
		शेष:
			dev_err(ac->dev, "Invalid codec profile 0x%x\n",
				codec_profile);
			rc = -EINVAL;
			जाओ err;
		पूर्ण
		अवरोध;
	हाल SND_AUDIOCODEC_ALAC:
		खोलो->dec_fmt_id = ASM_MEDIA_FMT_ALAC;
		अवरोध;
	हाल SND_AUDIOCODEC_APE:
		खोलो->dec_fmt_id = ASM_MEDIA_FMT_APE;
		अवरोध;
	शेष:
		dev_err(ac->dev, "Invalid format 0x%x\n", क्रमmat);
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);
	अगर (rc < 0)
		जाओ err;

	ac->io_mode |= ASM_TUN_WRITE_IO_MODE;

err:
	kमुक्त(pkt);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_खोलो_ग_लिखो);

अटल पूर्णांक __q6यंत्र_run(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
		       uपूर्णांक32_t flags, uपूर्णांक32_t msw_ts, uपूर्णांक32_t lsw_ts,
		       bool रुको)
अणु
	काष्ठा यंत्र_session_cmd_run_v2 *run;
	काष्ठा apr_pkt *pkt;
	पूर्णांक pkt_size, rc;
	व्योम *p;

	pkt_size = APR_HDR_SIZE + माप(*run);
	p = kzalloc(pkt_size, GFP_ATOMIC);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	run = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_SESSION_CMD_RUN_V2;
	run->flags = flags;
	run->समय_lsw = lsw_ts;
	run->समय_msw = msw_ts;
	अगर (रुको) अणु
		rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);
	पूर्ण अन्यथा अणु
		rc = apr_send_pkt(ac->adev, pkt);
		अगर (rc == pkt_size)
			rc = 0;
	पूर्ण

	kमुक्त(pkt);
	वापस rc;
पूर्ण

/**
 * q6यंत्र_run() - start the audio client
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id of q6यंत्र session
 * @flags: flags associated with ग_लिखो
 * @msw_ts: बारtamp msw
 * @lsw_ts: बारtamp lsw
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_run(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id, uपूर्णांक32_t flags,
	      uपूर्णांक32_t msw_ts, uपूर्णांक32_t lsw_ts)
अणु
	वापस __q6यंत्र_run(ac, stream_id, flags, msw_ts, lsw_ts, true);
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_run);

/**
 * q6यंत्र_run_noरुको() - start the audio client withou blocking
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id
 * @flags: flags associated with ग_लिखो
 * @msw_ts: बारtamp msw
 * @lsw_ts: बारtamp lsw
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_run_noरुको(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
		     uपूर्णांक32_t flags, uपूर्णांक32_t msw_ts, uपूर्णांक32_t lsw_ts)
अणु
	वापस __q6यंत्र_run(ac, stream_id, flags, msw_ts, lsw_ts, false);
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_run_noरुको);

/**
 * q6यंत्र_media_क्रमmat_block_multi_ch_pcm() - setup pcm configuration
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id
 * @rate: audio sample rate
 * @channels: number of audio channels.
 * @channel_map: channel map poपूर्णांकer
 * @bits_per_sample: bits per sample
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_media_क्रमmat_block_multi_ch_pcm(काष्ठा audio_client *ac,
					  uपूर्णांक32_t stream_id,
					  uपूर्णांक32_t rate, uपूर्णांक32_t channels,
					  u8 channel_map[PCM_MAX_NUM_CHANNEL],
					  uपूर्णांक16_t bits_per_sample)
अणु
	काष्ठा यंत्र_multi_channel_pcm_fmt_blk_v2 *fmt;
	काष्ठा apr_pkt *pkt;
	u8 *channel_mapping;
	व्योम *p;
	पूर्णांक rc, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(*fmt);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	fmt = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_blk.fmt_blk_size = माप(*fmt) - माप(fmt->fmt_blk);
	fmt->num_channels = channels;
	fmt->bits_per_sample = bits_per_sample;
	fmt->sample_rate = rate;
	fmt->is_चिन्हित = 1;

	channel_mapping = fmt->channel_mapping;

	अगर (channel_map) अणु
		स_नकल(channel_mapping, channel_map, PCM_MAX_NUM_CHANNEL);
	पूर्ण अन्यथा अणु
		अगर (q6dsp_map_channels(channel_mapping, channels)) अणु
			dev_err(ac->dev, " map channels failed %d\n", channels);
			rc = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);

err:
	kमुक्त(pkt);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_media_क्रमmat_block_multi_ch_pcm);

पूर्णांक q6यंत्र_stream_media_क्रमmat_block_flac(काष्ठा audio_client *ac,
					 uपूर्णांक32_t stream_id,
					 काष्ठा q6यंत्र_flac_cfg *cfg)
अणु
	काष्ठा यंत्र_flac_fmt_blk_v2 *fmt;
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	पूर्णांक rc, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(*fmt);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	fmt = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_blk.fmt_blk_size = माप(*fmt) - माप(fmt->fmt_blk);
	fmt->is_stream_info_present = cfg->stream_info_present;
	fmt->num_channels = cfg->ch_cfg;
	fmt->min_blk_size = cfg->min_blk_size;
	fmt->max_blk_size = cfg->max_blk_size;
	fmt->sample_rate = cfg->sample_rate;
	fmt->min_frame_size = cfg->min_frame_size;
	fmt->max_frame_size = cfg->max_frame_size;
	fmt->sample_size = cfg->sample_size;

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);
	kमुक्त(pkt);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_stream_media_क्रमmat_block_flac);

पूर्णांक q6यंत्र_stream_media_क्रमmat_block_wma_v9(काष्ठा audio_client *ac,
					   uपूर्णांक32_t stream_id,
					   काष्ठा q6यंत्र_wma_cfg *cfg)
अणु
	काष्ठा यंत्र_wmastdv9_fmt_blk_v2 *fmt;
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	पूर्णांक rc, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(*fmt);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	fmt = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_blk.fmt_blk_size = माप(*fmt) - माप(fmt->fmt_blk);
	fmt->fmtag = cfg->fmtag;
	fmt->num_channels = cfg->num_channels;
	fmt->sample_rate = cfg->sample_rate;
	fmt->bytes_per_sec = cfg->bytes_per_sec;
	fmt->blk_align = cfg->block_align;
	fmt->bits_per_sample = cfg->bits_per_sample;
	fmt->channel_mask = cfg->channel_mask;
	fmt->enc_options = cfg->enc_options;
	fmt->reserved = 0;

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);
	kमुक्त(pkt);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_stream_media_क्रमmat_block_wma_v9);

पूर्णांक q6यंत्र_stream_media_क्रमmat_block_wma_v10(काष्ठा audio_client *ac,
					    uपूर्णांक32_t stream_id,
					    काष्ठा q6यंत्र_wma_cfg *cfg)
अणु
	काष्ठा यंत्र_wmaprov10_fmt_blk_v2 *fmt;
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	पूर्णांक rc, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(*fmt);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	fmt = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_blk.fmt_blk_size = माप(*fmt) - माप(fmt->fmt_blk);
	fmt->fmtag = cfg->fmtag;
	fmt->num_channels = cfg->num_channels;
	fmt->sample_rate = cfg->sample_rate;
	fmt->bytes_per_sec = cfg->bytes_per_sec;
	fmt->blk_align = cfg->block_align;
	fmt->bits_per_sample = cfg->bits_per_sample;
	fmt->channel_mask = cfg->channel_mask;
	fmt->enc_options = cfg->enc_options;
	fmt->advanced_enc_options1 = cfg->adv_enc_options;
	fmt->advanced_enc_options2 = cfg->adv_enc_options2;

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);
	kमुक्त(pkt);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_stream_media_क्रमmat_block_wma_v10);

पूर्णांक q6यंत्र_stream_media_क्रमmat_block_alac(काष्ठा audio_client *ac,
					 uपूर्णांक32_t stream_id,
					 काष्ठा q6यंत्र_alac_cfg *cfg)
अणु
	काष्ठा यंत्र_alac_fmt_blk_v2 *fmt;
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	पूर्णांक rc, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(*fmt);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	fmt = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_blk.fmt_blk_size = माप(*fmt) - माप(fmt->fmt_blk);

	fmt->frame_length = cfg->frame_length;
	fmt->compatible_version = cfg->compatible_version;
	fmt->bit_depth =  cfg->bit_depth;
	fmt->num_channels = cfg->num_channels;
	fmt->max_run = cfg->max_run;
	fmt->max_frame_bytes = cfg->max_frame_bytes;
	fmt->avg_bit_rate = cfg->avg_bit_rate;
	fmt->sample_rate = cfg->sample_rate;
	fmt->channel_layout_tag = cfg->channel_layout_tag;
	fmt->pb = cfg->pb;
	fmt->mb = cfg->mb;
	fmt->kb = cfg->kb;

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);
	kमुक्त(pkt);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_stream_media_क्रमmat_block_alac);

पूर्णांक q6यंत्र_stream_media_क्रमmat_block_ape(काष्ठा audio_client *ac,
					uपूर्णांक32_t stream_id,
					काष्ठा q6यंत्र_ape_cfg *cfg)
अणु
	काष्ठा यंत्र_ape_fmt_blk_v2 *fmt;
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	पूर्णांक rc, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(*fmt);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	fmt = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_blk.fmt_blk_size = माप(*fmt) - माप(fmt->fmt_blk);

	fmt->compatible_version = cfg->compatible_version;
	fmt->compression_level = cfg->compression_level;
	fmt->क्रमmat_flags = cfg->क्रमmat_flags;
	fmt->blocks_per_frame = cfg->blocks_per_frame;
	fmt->final_frame_blocks = cfg->final_frame_blocks;
	fmt->total_frames = cfg->total_frames;
	fmt->bits_per_sample = cfg->bits_per_sample;
	fmt->num_channels = cfg->num_channels;
	fmt->sample_rate = cfg->sample_rate;
	fmt->seek_table_present = cfg->seek_table_present;

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);
	kमुक्त(pkt);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_stream_media_क्रमmat_block_ape);

अटल पूर्णांक q6यंत्र_stream_हटाओ_silence(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
				       uपूर्णांक32_t cmd,
				       uपूर्णांक32_t num_samples)
अणु
	uपूर्णांक32_t *samples;
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	पूर्णांक rc, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(uपूर्णांक32_t);
	p = kzalloc(pkt_size, GFP_ATOMIC);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	samples = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = cmd;
	*samples = num_samples;
	rc = apr_send_pkt(ac->adev, pkt);
	अगर (rc == pkt_size)
		rc = 0;

	kमुक्त(pkt);

	वापस rc;
पूर्ण

पूर्णांक q6यंत्र_stream_हटाओ_initial_silence(काष्ठा audio_client *ac,
					uपूर्णांक32_t stream_id,
					uपूर्णांक32_t initial_samples)
अणु
	वापस q6यंत्र_stream_हटाओ_silence(ac, stream_id,
					   ASM_DATA_CMD_REMOVE_INITIAL_SILENCE,
					   initial_samples);
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_stream_हटाओ_initial_silence);

पूर्णांक q6यंत्र_stream_हटाओ_trailing_silence(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
					 uपूर्णांक32_t trailing_samples)
अणु
	वापस q6यंत्र_stream_हटाओ_silence(ac, stream_id,
				   ASM_DATA_CMD_REMOVE_TRAILING_SILENCE,
				   trailing_samples);
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_stream_हटाओ_trailing_silence);

/**
 * q6यंत्र_enc_cfg_blk_pcm_क्रमmat_support() - setup pcm configuration क्रम capture
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id
 * @rate: audio sample rate
 * @channels: number of audio channels.
 * @bits_per_sample: bits per sample
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_enc_cfg_blk_pcm_क्रमmat_support(काष्ठा audio_client *ac,
					 uपूर्णांक32_t stream_id, uपूर्णांक32_t rate,
					 uपूर्णांक32_t channels,
					 uपूर्णांक16_t bits_per_sample)
अणु
	काष्ठा यंत्र_multi_channel_pcm_enc_cfg_v2  *enc_cfg;
	काष्ठा apr_pkt *pkt;
	u8 *channel_mapping;
	u32 frames_per_buf = 0;
	पूर्णांक pkt_size, rc;
	व्योम *p;

	pkt_size = APR_HDR_SIZE + माप(*enc_cfg);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	enc_cfg = p + APR_HDR_SIZE;
	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, true, stream_id);

	pkt->hdr.opcode = ASM_STREAM_CMD_SET_ENCDEC_PARAM;
	enc_cfg->encdec.param_id = ASM_PARAM_ID_ENCDEC_ENC_CFG_BLK_V2;
	enc_cfg->encdec.param_size = माप(*enc_cfg) - माप(enc_cfg->encdec);
	enc_cfg->encblk.frames_per_buf = frames_per_buf;
	enc_cfg->encblk.enc_cfg_blk_size  = enc_cfg->encdec.param_size -
					माप(काष्ठा यंत्र_enc_cfg_blk_param_v2);

	enc_cfg->num_channels = channels;
	enc_cfg->bits_per_sample = bits_per_sample;
	enc_cfg->sample_rate = rate;
	enc_cfg->is_चिन्हित = 1;
	channel_mapping = enc_cfg->channel_mapping;

	अगर (q6dsp_map_channels(channel_mapping, channels)) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);
err:
	kमुक्त(pkt);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_enc_cfg_blk_pcm_क्रमmat_support);


/**
 * q6यंत्र_पढ़ो() - पढ़ो data of period size from audio client
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_पढ़ो(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id)
अणु
	काष्ठा यंत्र_data_cmd_पढ़ो_v2 *पढ़ो;
	काष्ठा audio_port_data *port;
	काष्ठा audio_buffer *ab;
	काष्ठा apr_pkt *pkt;
	अचिन्हित दीर्घ flags;
	पूर्णांक pkt_size;
	पूर्णांक rc = 0;
	व्योम *p;

	pkt_size = APR_HDR_SIZE + माप(*पढ़ो);
	p = kzalloc(pkt_size, GFP_ATOMIC);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	पढ़ो = p + APR_HDR_SIZE;

	spin_lock_irqsave(&ac->lock, flags);
	port = &ac->port[SNDRV_PCM_STREAM_CAPTURE];
	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, false, stream_id);
	ab = &port->buf[port->dsp_buf];
	pkt->hdr.opcode = ASM_DATA_CMD_READ_V2;
	पढ़ो->buf_addr_lsw = lower_32_bits(ab->phys);
	पढ़ो->buf_addr_msw = upper_32_bits(ab->phys);
	पढ़ो->mem_map_handle = port->mem_map_handle;

	पढ़ो->buf_size = ab->size;
	पढ़ो->seq_id = port->dsp_buf;
	pkt->hdr.token = port->dsp_buf;

	port->dsp_buf++;

	अगर (port->dsp_buf >= port->num_periods)
		port->dsp_buf = 0;

	spin_unlock_irqrestore(&ac->lock, flags);
	rc = apr_send_pkt(ac->adev, pkt);
	अगर (rc == pkt_size)
		rc = 0;
	अन्यथा
		pr_err("read op[0x%x]rc[%d]\n", pkt->hdr.opcode, rc);

	kमुक्त(pkt);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_पढ़ो);

अटल पूर्णांक __q6यंत्र_खोलो_पढ़ो(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
		uपूर्णांक32_t क्रमmat, uपूर्णांक16_t bits_per_sample)
अणु
	काष्ठा यंत्र_stream_cmd_खोलो_पढ़ो_v3 *खोलो;
	काष्ठा apr_pkt *pkt;
	पूर्णांक pkt_size, rc;
	व्योम *p;

	pkt_size = APR_HDR_SIZE + माप(*खोलो);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	खोलो = p + APR_HDR_SIZE;

	q6यंत्र_add_hdr(ac, &pkt->hdr,  pkt_size, true, stream_id);
	pkt->hdr.opcode = ASM_STREAM_CMD_OPEN_READ_V3;
	/* Stream prio : High, provide meta info with encoded frames */
	खोलो->src_endpoपूर्णांकype = ASM_END_POINT_DEVICE_MATRIX;

	खोलो->preprocopo_id = ASM_STREAM_POSTPROC_TOPO_ID_NONE;
	खोलो->bits_per_sample = bits_per_sample;
	खोलो->mode_flags = 0x0;

	खोलो->mode_flags |= ASM_LEGACY_STREAM_SESSION <<
				ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_READ;

	चयन (क्रमmat) अणु
	हाल FORMAT_LINEAR_PCM:
		खोलो->mode_flags |= 0x00;
		खोलो->enc_cfg_id = ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2;
		अवरोध;
	शेष:
		pr_err("Invalid format[%d]\n", क्रमmat);
	पूर्ण

	rc = q6यंत्र_ac_send_cmd_sync(ac, pkt);

	kमुक्त(pkt);
	वापस rc;
पूर्ण

/**
 * q6यंत्र_खोलो_पढ़ो() - Open audio client क्रम पढ़ोing
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id
 * @क्रमmat: audio sample क्रमmat
 * @bits_per_sample: bits per sample
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_खोलो_पढ़ो(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id,
		    uपूर्णांक32_t क्रमmat, uपूर्णांक16_t bits_per_sample)
अणु
	वापस __q6यंत्र_खोलो_पढ़ो(ac, stream_id, क्रमmat, bits_per_sample);
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_खोलो_पढ़ो);

/**
 * q6यंत्र_ग_लिखो_async() - non blocking ग_लिखो
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id
 * @len: length in bytes
 * @msw_ts: बारtamp msw
 * @lsw_ts: बारtamp lsw
 * @wflags: flags associated with ग_लिखो
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_ग_लिखो_async(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id, uपूर्णांक32_t len,
		      uपूर्णांक32_t msw_ts, uपूर्णांक32_t lsw_ts, uपूर्णांक32_t wflags)
अणु
	काष्ठा यंत्र_data_cmd_ग_लिखो_v2 *ग_लिखो;
	काष्ठा audio_port_data *port;
	काष्ठा audio_buffer *ab;
	अचिन्हित दीर्घ flags;
	काष्ठा apr_pkt *pkt;
	पूर्णांक pkt_size;
	पूर्णांक rc = 0;
	व्योम *p;

	pkt_size = APR_HDR_SIZE + माप(*ग_लिखो);
	p = kzalloc(pkt_size, GFP_ATOMIC);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	ग_लिखो = p + APR_HDR_SIZE;

	spin_lock_irqsave(&ac->lock, flags);
	port = &ac->port[SNDRV_PCM_STREAM_PLAYBACK];
	q6यंत्र_add_hdr(ac, &pkt->hdr, pkt_size, false, stream_id);

	ab = &port->buf[port->dsp_buf];
	pkt->hdr.token = port->dsp_buf | (len << ASM_WRITE_TOKEN_LEN_SHIFT);
	pkt->hdr.opcode = ASM_DATA_CMD_WRITE_V2;
	ग_लिखो->buf_addr_lsw = lower_32_bits(ab->phys);
	ग_लिखो->buf_addr_msw = upper_32_bits(ab->phys);
	ग_लिखो->buf_size = len;
	ग_लिखो->seq_id = port->dsp_buf;
	ग_लिखो->बारtamp_lsw = lsw_ts;
	ग_लिखो->बारtamp_msw = msw_ts;
	ग_लिखो->mem_map_handle =
	    ac->port[SNDRV_PCM_STREAM_PLAYBACK].mem_map_handle;

	ग_लिखो->flags = wflags;

	port->dsp_buf++;

	अगर (port->dsp_buf >= port->num_periods)
		port->dsp_buf = 0;

	spin_unlock_irqrestore(&ac->lock, flags);
	rc = apr_send_pkt(ac->adev, pkt);
	अगर (rc == pkt_size)
		rc = 0;

	kमुक्त(pkt);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_ग_लिखो_async);

अटल व्योम q6यंत्र_reset_buf_state(काष्ठा audio_client *ac)
अणु
	काष्ठा audio_port_data *port = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ac->lock, flags);
	port = &ac->port[SNDRV_PCM_STREAM_PLAYBACK];
	port->dsp_buf = 0;
	port = &ac->port[SNDRV_PCM_STREAM_CAPTURE];
	port->dsp_buf = 0;
	spin_unlock_irqrestore(&ac->lock, flags);
पूर्ण

अटल पूर्णांक __q6यंत्र_cmd(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id, पूर्णांक cmd,
		       bool रुको)
अणु
	काष्ठा apr_pkt pkt;
	पूर्णांक rc;

	q6यंत्र_add_hdr(ac, &pkt.hdr, APR_HDR_SIZE, true, stream_id);

	चयन (cmd) अणु
	हाल CMD_PAUSE:
		pkt.hdr.opcode = ASM_SESSION_CMD_PAUSE;
		अवरोध;
	हाल CMD_SUSPEND:
		pkt.hdr.opcode = ASM_SESSION_CMD_SUSPEND;
		अवरोध;
	हाल CMD_FLUSH:
		pkt.hdr.opcode = ASM_STREAM_CMD_FLUSH;
		अवरोध;
	हाल CMD_OUT_FLUSH:
		pkt.hdr.opcode = ASM_STREAM_CMD_FLUSH_READBUFS;
		अवरोध;
	हाल CMD_EOS:
		pkt.hdr.opcode = ASM_DATA_CMD_EOS;
		अवरोध;
	हाल CMD_CLOSE:
		pkt.hdr.opcode = ASM_STREAM_CMD_CLOSE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (रुको)
		rc = q6यंत्र_ac_send_cmd_sync(ac, &pkt);
	अन्यथा
		वापस apr_send_pkt(ac->adev, &pkt);

	अगर (rc < 0)
		वापस rc;

	अगर (cmd == CMD_FLUSH)
		q6यंत्र_reset_buf_state(ac);

	वापस 0;
पूर्ण

/**
 * q6यंत्र_cmd() - run cmd on audio client
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id
 * @cmd: command to run on audio client.
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_cmd(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id, पूर्णांक cmd)
अणु
	वापस __q6यंत्र_cmd(ac, stream_id, cmd, true);
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_cmd);

/**
 * q6यंत्र_cmd_noरुको() - non blocking, run cmd on audio client
 *
 * @ac: audio client poपूर्णांकer
 * @stream_id: stream id
 * @cmd: command to run on audio client.
 *
 * Return: Will be an negative value on error or zero on success
 */
पूर्णांक q6यंत्र_cmd_noरुको(काष्ठा audio_client *ac, uपूर्णांक32_t stream_id, पूर्णांक cmd)
अणु
	वापस __q6यंत्र_cmd(ac, stream_id, cmd, false);
पूर्ण
EXPORT_SYMBOL_GPL(q6यंत्र_cmd_noरुको);

अटल पूर्णांक q6यंत्र_probe(काष्ठा apr_device *adev)
अणु
	काष्ठा device *dev = &adev->dev;
	काष्ठा q6यंत्र *q6यंत्र;

	q6यंत्र = devm_kzalloc(dev, माप(*q6यंत्र), GFP_KERNEL);
	अगर (!q6यंत्र)
		वापस -ENOMEM;

	q6core_get_svc_api_info(adev->svc_id, &q6यंत्र->ainfo);

	q6यंत्र->dev = dev;
	q6यंत्र->adev = adev;
	init_रुकोqueue_head(&q6यंत्र->mem_रुको);
	spin_lock_init(&q6यंत्र->slock);
	dev_set_drvdata(dev, q6यंत्र);

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id q6यंत्र_device_id[]  = अणु
	अणु .compatible = "qcom,q6asm" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6यंत्र_device_id);
#पूर्ण_अगर

अटल काष्ठा apr_driver qcom_q6यंत्र_driver = अणु
	.probe = q6यंत्र_probe,
	.callback = q6यंत्र_srvc_callback,
	.driver = अणु
		.name = "qcom-q6asm",
		.of_match_table = of_match_ptr(q6यंत्र_device_id),
	पूर्ण,
पूर्ण;

module_apr_driver(qcom_q6यंत्र_driver);
MODULE_DESCRIPTION("Q6 Audio Stream Manager driver");
MODULE_LICENSE("GPL v2");
