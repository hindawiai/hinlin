<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008
 * Guennadi Liakhovetski, DENX Software Engineering, <lg@denx.de>
 *
 * Copyright (C) 2005-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/clk.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/dma/ipu-dma.h>

#समावेश "../dmaengine.h"
#समावेश "ipu_intern.h"

#घोषणा FS_VF_IN_VALID	0x00000002
#घोषणा FS_ENC_IN_VALID	0x00000001

अटल पूर्णांक ipu_disable_channel(काष्ठा idmac *idmac, काष्ठा idmac_channel *ichan,
			       bool रुको_क्रम_stop);

/*
 * There can be only one, we could allocate it dynamically, but then we'd have
 * to add an extra parameter to some functions, and use something as ugly as
 *	काष्ठा ipu *ipu = to_ipu(to_idmac(ichan->dma_chan.device));
 * in the ISR
 */
अटल काष्ठा ipu ipu_data;

#घोषणा to_ipu(id) container_of(id, काष्ठा ipu, idmac)

अटल u32 __idmac_पढ़ो_icreg(काष्ठा ipu *ipu, अचिन्हित दीर्घ reg)
अणु
	वापस __raw_पढ़ोl(ipu->reg_ic + reg);
पूर्ण

#घोषणा idmac_पढ़ो_icreg(ipu, reg) __idmac_पढ़ो_icreg(ipu, reg - IC_CONF)

अटल व्योम __idmac_ग_लिखो_icreg(काष्ठा ipu *ipu, u32 value, अचिन्हित दीर्घ reg)
अणु
	__raw_ग_लिखोl(value, ipu->reg_ic + reg);
पूर्ण

#घोषणा idmac_ग_लिखो_icreg(ipu, v, reg) __idmac_ग_लिखो_icreg(ipu, v, reg - IC_CONF)

अटल u32 idmac_पढ़ो_ipureg(काष्ठा ipu *ipu, अचिन्हित दीर्घ reg)
अणु
	वापस __raw_पढ़ोl(ipu->reg_ipu + reg);
पूर्ण

अटल व्योम idmac_ग_लिखो_ipureg(काष्ठा ipu *ipu, u32 value, अचिन्हित दीर्घ reg)
अणु
	__raw_ग_लिखोl(value, ipu->reg_ipu + reg);
पूर्ण

/*****************************************************************************
 * IPU / IC common functions
 */
अटल व्योम dump_idmac_reg(काष्ठा ipu *ipu)
अणु
	dev_dbg(ipu->dev, "IDMAC_CONF 0x%x, IC_CONF 0x%x, IDMAC_CHA_EN 0x%x, "
		"IDMAC_CHA_PRI 0x%x, IDMAC_CHA_BUSY 0x%x\n",
		idmac_पढ़ो_icreg(ipu, IDMAC_CONF),
		idmac_पढ़ो_icreg(ipu, IC_CONF),
		idmac_पढ़ो_icreg(ipu, IDMAC_CHA_EN),
		idmac_पढ़ो_icreg(ipu, IDMAC_CHA_PRI),
		idmac_पढ़ो_icreg(ipu, IDMAC_CHA_BUSY));
	dev_dbg(ipu->dev, "BUF0_RDY 0x%x, BUF1_RDY 0x%x, CUR_BUF 0x%x, "
		"DB_MODE 0x%x, TASKS_STAT 0x%x\n",
		idmac_पढ़ो_ipureg(ipu, IPU_CHA_BUF0_RDY),
		idmac_पढ़ो_ipureg(ipu, IPU_CHA_BUF1_RDY),
		idmac_पढ़ो_ipureg(ipu, IPU_CHA_CUR_BUF),
		idmac_पढ़ो_ipureg(ipu, IPU_CHA_DB_MODE_SEL),
		idmac_पढ़ो_ipureg(ipu, IPU_TASKS_STAT));
पूर्ण

अटल uपूर्णांक32_t bytes_per_pixel(क्रमागत pixel_fmt fmt)
अणु
	चयन (fmt) अणु
	हाल IPU_PIX_FMT_GENERIC:	/* generic data */
	हाल IPU_PIX_FMT_RGB332:
	हाल IPU_PIX_FMT_YUV420P:
	हाल IPU_PIX_FMT_YUV422P:
	शेष:
		वापस 1;
	हाल IPU_PIX_FMT_RGB565:
	हाल IPU_PIX_FMT_YUYV:
	हाल IPU_PIX_FMT_UYVY:
		वापस 2;
	हाल IPU_PIX_FMT_BGR24:
	हाल IPU_PIX_FMT_RGB24:
		वापस 3;
	हाल IPU_PIX_FMT_GENERIC_32:	/* generic data */
	हाल IPU_PIX_FMT_BGR32:
	हाल IPU_PIX_FMT_RGB32:
	हाल IPU_PIX_FMT_ABGR32:
		वापस 4;
	पूर्ण
पूर्ण

/* Enable direct ग_लिखो to memory by the Camera Sensor Interface */
अटल व्योम ipu_ic_enable_task(काष्ठा ipu *ipu, क्रमागत ipu_channel channel)
अणु
	uपूर्णांक32_t ic_conf, mask;

	चयन (channel) अणु
	हाल IDMAC_IC_0:
		mask = IC_CONF_PRPENC_EN;
		अवरोध;
	हाल IDMAC_IC_7:
		mask = IC_CONF_RWS_EN | IC_CONF_PRPENC_EN;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	ic_conf = idmac_पढ़ो_icreg(ipu, IC_CONF) | mask;
	idmac_ग_लिखो_icreg(ipu, ic_conf, IC_CONF);
पूर्ण

/* Called under spin_lock_irqsave(&ipu_data.lock) */
अटल व्योम ipu_ic_disable_task(काष्ठा ipu *ipu, क्रमागत ipu_channel channel)
अणु
	uपूर्णांक32_t ic_conf, mask;

	चयन (channel) अणु
	हाल IDMAC_IC_0:
		mask = IC_CONF_PRPENC_EN;
		अवरोध;
	हाल IDMAC_IC_7:
		mask = IC_CONF_RWS_EN | IC_CONF_PRPENC_EN;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	ic_conf = idmac_पढ़ो_icreg(ipu, IC_CONF) & ~mask;
	idmac_ग_लिखो_icreg(ipu, ic_conf, IC_CONF);
पूर्ण

अटल uपूर्णांक32_t ipu_channel_status(काष्ठा ipu *ipu, क्रमागत ipu_channel channel)
अणु
	uपूर्णांक32_t stat = TASK_STAT_IDLE;
	uपूर्णांक32_t task_stat_reg = idmac_पढ़ो_ipureg(ipu, IPU_TASKS_STAT);

	चयन (channel) अणु
	हाल IDMAC_IC_7:
		stat = (task_stat_reg & TSTAT_CSI2MEM_MASK) >>
			TSTAT_CSI2MEM_OFFSET;
		अवरोध;
	हाल IDMAC_IC_0:
	हाल IDMAC_SDC_0:
	हाल IDMAC_SDC_1:
	शेष:
		अवरोध;
	पूर्ण
	वापस stat;
पूर्ण

काष्ठा chan_param_mem_planar अणु
	/* Word 0 */
	u32	xv:10;
	u32	yv:10;
	u32	xb:12;

	u32	yb:12;
	u32	res1:2;
	u32	nsb:1;
	u32	lnpb:6;
	u32	ubo_l:11;

	u32	ubo_h:15;
	u32	vbo_l:17;

	u32	vbo_h:9;
	u32	res2:3;
	u32	fw:12;
	u32	fh_l:8;

	u32	fh_h:4;
	u32	res3:28;

	/* Word 1 */
	u32	eba0;

	u32	eba1;

	u32	bpp:3;
	u32	sl:14;
	u32	pfs:3;
	u32	bam:3;
	u32	res4:2;
	u32	npb:6;
	u32	res5:1;

	u32	sat:2;
	u32	res6:30;
पूर्ण __attribute__ ((packed));

काष्ठा chan_param_mem_पूर्णांकerleaved अणु
	/* Word 0 */
	u32	xv:10;
	u32	yv:10;
	u32	xb:12;

	u32	yb:12;
	u32	sce:1;
	u32	res1:1;
	u32	nsb:1;
	u32	lnpb:6;
	u32	sx:10;
	u32	sy_l:1;

	u32	sy_h:9;
	u32	ns:10;
	u32	sm:10;
	u32	sdx_l:3;

	u32	sdx_h:2;
	u32	sdy:5;
	u32	sdrx:1;
	u32	sdry:1;
	u32	sdr1:1;
	u32	res2:2;
	u32	fw:12;
	u32	fh_l:8;

	u32	fh_h:4;
	u32	res3:28;

	/* Word 1 */
	u32	eba0;

	u32	eba1;

	u32	bpp:3;
	u32	sl:14;
	u32	pfs:3;
	u32	bam:3;
	u32	res4:2;
	u32	npb:6;
	u32	res5:1;

	u32	sat:2;
	u32	scc:1;
	u32	ofs0:5;
	u32	ofs1:5;
	u32	ofs2:5;
	u32	ofs3:5;
	u32	wid0:3;
	u32	wid1:3;
	u32	wid2:3;

	u32	wid3:3;
	u32	dec_sel:1;
	u32	res6:28;
पूर्ण __attribute__ ((packed));

जोड़ chan_param_mem अणु
	काष्ठा chan_param_mem_planar		pp;
	काष्ठा chan_param_mem_पूर्णांकerleaved	ip;
पूर्ण;

अटल व्योम ipu_ch_param_set_plane_offset(जोड़ chan_param_mem *params,
					  u32 u_offset, u32 v_offset)
अणु
	params->pp.ubo_l = u_offset & 0x7ff;
	params->pp.ubo_h = u_offset >> 11;
	params->pp.vbo_l = v_offset & 0x1ffff;
	params->pp.vbo_h = v_offset >> 17;
पूर्ण

अटल व्योम ipu_ch_param_set_size(जोड़ chan_param_mem *params,
				  uपूर्णांक32_t pixel_fmt, uपूर्णांक16_t width,
				  uपूर्णांक16_t height, uपूर्णांक16_t stride)
अणु
	u32 u_offset;
	u32 v_offset;

	params->pp.fw		= width - 1;
	params->pp.fh_l		= height - 1;
	params->pp.fh_h		= (height - 1) >> 8;
	params->pp.sl		= stride - 1;

	चयन (pixel_fmt) अणु
	हाल IPU_PIX_FMT_GENERIC:
		/*Represents 8-bit Generic data */
		params->pp.bpp	= 3;
		params->pp.pfs	= 7;
		params->pp.npb	= 31;
		params->pp.sat	= 2;		/* SAT = use 32-bit access */
		अवरोध;
	हाल IPU_PIX_FMT_GENERIC_32:
		/*Represents 32-bit Generic data */
		params->pp.bpp	= 0;
		params->pp.pfs	= 7;
		params->pp.npb	= 7;
		params->pp.sat	= 2;		/* SAT = use 32-bit access */
		अवरोध;
	हाल IPU_PIX_FMT_RGB565:
		params->ip.bpp	= 2;
		params->ip.pfs	= 4;
		params->ip.npb	= 15;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 0;		/* Red bit offset */
		params->ip.ofs1	= 5;		/* Green bit offset */
		params->ip.ofs2	= 11;		/* Blue bit offset */
		params->ip.ofs3	= 16;		/* Alpha bit offset */
		params->ip.wid0	= 4;		/* Red bit width - 1 */
		params->ip.wid1	= 5;		/* Green bit width - 1 */
		params->ip.wid2	= 4;		/* Blue bit width - 1 */
		अवरोध;
	हाल IPU_PIX_FMT_BGR24:
		params->ip.bpp	= 1;		/* 24 BPP & RGB PFS */
		params->ip.pfs	= 4;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 0;		/* Red bit offset */
		params->ip.ofs1	= 8;		/* Green bit offset */
		params->ip.ofs2	= 16;		/* Blue bit offset */
		params->ip.ofs3	= 24;		/* Alpha bit offset */
		params->ip.wid0	= 7;		/* Red bit width - 1 */
		params->ip.wid1	= 7;		/* Green bit width - 1 */
		params->ip.wid2	= 7;		/* Blue bit width - 1 */
		अवरोध;
	हाल IPU_PIX_FMT_RGB24:
		params->ip.bpp	= 1;		/* 24 BPP & RGB PFS */
		params->ip.pfs	= 4;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 16;		/* Red bit offset */
		params->ip.ofs1	= 8;		/* Green bit offset */
		params->ip.ofs2	= 0;		/* Blue bit offset */
		params->ip.ofs3	= 24;		/* Alpha bit offset */
		params->ip.wid0	= 7;		/* Red bit width - 1 */
		params->ip.wid1	= 7;		/* Green bit width - 1 */
		params->ip.wid2	= 7;		/* Blue bit width - 1 */
		अवरोध;
	हाल IPU_PIX_FMT_BGRA32:
	हाल IPU_PIX_FMT_BGR32:
	हाल IPU_PIX_FMT_ABGR32:
		params->ip.bpp	= 0;
		params->ip.pfs	= 4;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 8;		/* Red bit offset */
		params->ip.ofs1	= 16;		/* Green bit offset */
		params->ip.ofs2	= 24;		/* Blue bit offset */
		params->ip.ofs3	= 0;		/* Alpha bit offset */
		params->ip.wid0	= 7;		/* Red bit width - 1 */
		params->ip.wid1	= 7;		/* Green bit width - 1 */
		params->ip.wid2	= 7;		/* Blue bit width - 1 */
		params->ip.wid3	= 7;		/* Alpha bit width - 1 */
		अवरोध;
	हाल IPU_PIX_FMT_RGBA32:
	हाल IPU_PIX_FMT_RGB32:
		params->ip.bpp	= 0;
		params->ip.pfs	= 4;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 24;		/* Red bit offset */
		params->ip.ofs1	= 16;		/* Green bit offset */
		params->ip.ofs2	= 8;		/* Blue bit offset */
		params->ip.ofs3	= 0;		/* Alpha bit offset */
		params->ip.wid0	= 7;		/* Red bit width - 1 */
		params->ip.wid1	= 7;		/* Green bit width - 1 */
		params->ip.wid2	= 7;		/* Blue bit width - 1 */
		params->ip.wid3	= 7;		/* Alpha bit width - 1 */
		अवरोध;
	हाल IPU_PIX_FMT_UYVY:
		params->ip.bpp	= 2;
		params->ip.pfs	= 6;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		अवरोध;
	हाल IPU_PIX_FMT_YUV420P2:
	हाल IPU_PIX_FMT_YUV420P:
		params->ip.bpp	= 3;
		params->ip.pfs	= 3;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		u_offset = stride * height;
		v_offset = u_offset + u_offset / 4;
		ipu_ch_param_set_plane_offset(params, u_offset, v_offset);
		अवरोध;
	हाल IPU_PIX_FMT_YVU422P:
		params->ip.bpp	= 3;
		params->ip.pfs	= 2;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		v_offset = stride * height;
		u_offset = v_offset + v_offset / 2;
		ipu_ch_param_set_plane_offset(params, u_offset, v_offset);
		अवरोध;
	हाल IPU_PIX_FMT_YUV422P:
		params->ip.bpp	= 3;
		params->ip.pfs	= 2;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		u_offset = stride * height;
		v_offset = u_offset + u_offset / 2;
		ipu_ch_param_set_plane_offset(params, u_offset, v_offset);
		अवरोध;
	शेष:
		dev_err(ipu_data.dev,
			"mx3 ipu: unimplemented pixel format %d\n", pixel_fmt);
		अवरोध;
	पूर्ण

	params->pp.nsb = 1;
पूर्ण

अटल व्योम ipu_ch_param_set_buffer(जोड़ chan_param_mem *params,
				    dma_addr_t buf0, dma_addr_t buf1)
अणु
	params->pp.eba0 = buf0;
	params->pp.eba1 = buf1;
पूर्ण

अटल व्योम ipu_ch_param_set_rotation(जोड़ chan_param_mem *params,
				      क्रमागत ipu_rotate_mode rotate)
अणु
	params->pp.bam = rotate;
पूर्ण

अटल व्योम ipu_ग_लिखो_param_mem(uपूर्णांक32_t addr, uपूर्णांक32_t *data,
				uपूर्णांक32_t num_words)
अणु
	क्रम (; num_words > 0; num_words--) अणु
		dev_dbg(ipu_data.dev,
			"write param mem - addr = 0x%08X, data = 0x%08X\n",
			addr, *data);
		idmac_ग_लिखो_ipureg(&ipu_data, addr, IPU_IMA_ADDR);
		idmac_ग_लिखो_ipureg(&ipu_data, *data++, IPU_IMA_DATA);
		addr++;
		अगर ((addr & 0x7) == 5) अणु
			addr &= ~0x7;	/* set to word 0 */
			addr += 8;	/* increment to next row */
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक calc_resize_coeffs(uपूर्णांक32_t in_size, uपूर्णांक32_t out_size,
			      uपूर्णांक32_t *resize_coeff,
			      uपूर्णांक32_t *करोwnsize_coeff)
अणु
	uपूर्णांक32_t temp_size;
	uपूर्णांक32_t temp_करोwnsize;

	*resize_coeff	= 1 << 13;
	*करोwnsize_coeff	= 1 << 13;

	/* Cannot करोwnsize more than 8:1 */
	अगर (out_size << 3 < in_size)
		वापस -EINVAL;

	/* compute करोwnsizing coefficient */
	temp_करोwnsize = 0;
	temp_size = in_size;
	जबतक (temp_size >= out_size * 2 && temp_करोwnsize < 2) अणु
		temp_size >>= 1;
		temp_करोwnsize++;
	पूर्ण
	*करोwnsize_coeff = temp_करोwnsize;

	/*
	 * compute resizing coefficient using the following क्रमmula:
	 * resize_coeff = M*(SI -1)/(SO - 1)
	 * where M = 2^13, SI - input size, SO - output size
	 */
	*resize_coeff = (8192L * (temp_size - 1)) / (out_size - 1);
	अगर (*resize_coeff >= 16384L) अणु
		dev_err(ipu_data.dev, "Warning! Overflow on resize coeff.\n");
		*resize_coeff = 0x3FFF;
	पूर्ण

	dev_dbg(ipu_data.dev, "resizing from %u -> %u pixels, "
		"downsize=%u, resize=%u.%lu (reg=%u)\n", in_size, out_size,
		*करोwnsize_coeff, *resize_coeff >= 8192L ? 1 : 0,
		((*resize_coeff & 0x1FFF) * 10000L) / 8192L, *resize_coeff);

	वापस 0;
पूर्ण

अटल क्रमागत ipu_color_space क्रमmat_to_colorspace(क्रमागत pixel_fmt fmt)
अणु
	चयन (fmt) अणु
	हाल IPU_PIX_FMT_RGB565:
	हाल IPU_PIX_FMT_BGR24:
	हाल IPU_PIX_FMT_RGB24:
	हाल IPU_PIX_FMT_BGR32:
	हाल IPU_PIX_FMT_RGB32:
		वापस IPU_COLORSPACE_RGB;
	शेष:
		वापस IPU_COLORSPACE_YCBCR;
	पूर्ण
पूर्ण

अटल पूर्णांक ipu_ic_init_prpenc(काष्ठा ipu *ipu,
			      जोड़ ipu_channel_param *params, bool src_is_csi)
अणु
	uपूर्णांक32_t reg, ic_conf;
	uपूर्णांक32_t करोwnsize_coeff, resize_coeff;
	क्रमागत ipu_color_space in_fmt, out_fmt;

	/* Setup vertical resizing */
	calc_resize_coeffs(params->video.in_height,
			    params->video.out_height,
			    &resize_coeff, &करोwnsize_coeff);
	reg = (करोwnsize_coeff << 30) | (resize_coeff << 16);

	/* Setup horizontal resizing */
	calc_resize_coeffs(params->video.in_width,
			    params->video.out_width,
			    &resize_coeff, &करोwnsize_coeff);
	reg |= (करोwnsize_coeff << 14) | resize_coeff;

	/* Setup color space conversion */
	in_fmt = क्रमmat_to_colorspace(params->video.in_pixel_fmt);
	out_fmt = क्रमmat_to_colorspace(params->video.out_pixel_fmt);

	/*
	 * Colourspace conversion unsupported yet - see _init_csc() in
	 * Freescale sources
	 */
	अगर (in_fmt != out_fmt) अणु
		dev_err(ipu->dev, "Colourspace conversion unsupported!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	idmac_ग_लिखो_icreg(ipu, reg, IC_PRP_ENC_RSC);

	ic_conf = idmac_पढ़ो_icreg(ipu, IC_CONF);

	अगर (src_is_csi)
		ic_conf &= ~IC_CONF_RWS_EN;
	अन्यथा
		ic_conf |= IC_CONF_RWS_EN;

	idmac_ग_लिखो_icreg(ipu, ic_conf, IC_CONF);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t dma_param_addr(uपूर्णांक32_t dma_ch)
अणु
	/* Channel Parameter Memory */
	वापस 0x10000 | (dma_ch << 4);
पूर्ण

अटल व्योम ipu_channel_set_priority(काष्ठा ipu *ipu, क्रमागत ipu_channel channel,
				     bool prio)
अणु
	u32 reg = idmac_पढ़ो_icreg(ipu, IDMAC_CHA_PRI);

	अगर (prio)
		reg |= 1UL << channel;
	अन्यथा
		reg &= ~(1UL << channel);

	idmac_ग_लिखो_icreg(ipu, reg, IDMAC_CHA_PRI);

	dump_idmac_reg(ipu);
पूर्ण

अटल uपूर्णांक32_t ipu_channel_conf_mask(क्रमागत ipu_channel channel)
अणु
	uपूर्णांक32_t mask;

	चयन (channel) अणु
	हाल IDMAC_IC_0:
	हाल IDMAC_IC_7:
		mask = IPU_CONF_CSI_EN | IPU_CONF_IC_EN;
		अवरोध;
	हाल IDMAC_SDC_0:
	हाल IDMAC_SDC_1:
		mask = IPU_CONF_SDC_EN | IPU_CONF_DI_EN;
		अवरोध;
	शेष:
		mask = 0;
		अवरोध;
	पूर्ण

	वापस mask;
पूर्ण

/**
 * ipu_enable_channel() - enable an IPU channel.
 * @idmac:	IPU DMAC context.
 * @ichan:	IDMAC channel.
 * @वापस:	0 on success or negative error code on failure.
 */
अटल पूर्णांक ipu_enable_channel(काष्ठा idmac *idmac, काष्ठा idmac_channel *ichan)
अणु
	काष्ठा ipu *ipu = to_ipu(idmac);
	क्रमागत ipu_channel channel = ichan->dma_chan.chan_id;
	uपूर्णांक32_t reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipu->lock, flags);

	/* Reset to buffer 0 */
	idmac_ग_लिखो_ipureg(ipu, 1UL << channel, IPU_CHA_CUR_BUF);
	ichan->active_buffer = 0;
	ichan->status = IPU_CHANNEL_ENABLED;

	चयन (channel) अणु
	हाल IDMAC_SDC_0:
	हाल IDMAC_SDC_1:
	हाल IDMAC_IC_7:
		ipu_channel_set_priority(ipu, channel, true);
	शेष:
		अवरोध;
	पूर्ण

	reg = idmac_पढ़ो_icreg(ipu, IDMAC_CHA_EN);

	idmac_ग_लिखो_icreg(ipu, reg | (1UL << channel), IDMAC_CHA_EN);

	ipu_ic_enable_task(ipu, channel);

	spin_unlock_irqrestore(&ipu->lock, flags);
	वापस 0;
पूर्ण

/**
 * ipu_init_channel_buffer() - initialize a buffer क्रम logical IPU channel.
 * @ichan:	IDMAC channel.
 * @pixel_fmt:	pixel क्रमmat of buffer. Pixel क्रमmat is a FOURCC ASCII code.
 * @width:	width of buffer in pixels.
 * @height:	height of buffer in pixels.
 * @stride:	stride length of buffer in pixels.
 * @rot_mode:	rotation mode of buffer. A rotation setting other than
 *		IPU_ROTATE_VERT_FLIP should only be used क्रम input buffers of
 *		rotation channels.
 * @phyaddr_0:	buffer 0 physical address.
 * @phyaddr_1:	buffer 1 physical address. Setting this to a value other than
 *		शून्य enables द्विगुन buffering mode.
 * @वापस:	0 on success or negative error code on failure.
 */
अटल पूर्णांक ipu_init_channel_buffer(काष्ठा idmac_channel *ichan,
				   क्रमागत pixel_fmt pixel_fmt,
				   uपूर्णांक16_t width, uपूर्णांक16_t height,
				   uपूर्णांक32_t stride,
				   क्रमागत ipu_rotate_mode rot_mode,
				   dma_addr_t phyaddr_0, dma_addr_t phyaddr_1)
अणु
	क्रमागत ipu_channel channel = ichan->dma_chan.chan_id;
	काष्ठा idmac *idmac = to_idmac(ichan->dma_chan.device);
	काष्ठा ipu *ipu = to_ipu(idmac);
	जोड़ chan_param_mem params = अणुपूर्ण;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t reg;
	uपूर्णांक32_t stride_bytes;

	stride_bytes = stride * bytes_per_pixel(pixel_fmt);

	अगर (stride_bytes % 4) अणु
		dev_err(ipu->dev,
			"Stride length must be 32-bit aligned, stride = %d, bytes = %d\n",
			stride, stride_bytes);
		वापस -EINVAL;
	पूर्ण

	/* IC channel's stride must be a multiple of 8 pixels */
	अगर ((channel <= IDMAC_IC_13) && (stride % 8)) अणु
		dev_err(ipu->dev, "Stride must be 8 pixel multiple\n");
		वापस -EINVAL;
	पूर्ण

	/* Build parameter memory data क्रम DMA channel */
	ipu_ch_param_set_size(&params, pixel_fmt, width, height, stride_bytes);
	ipu_ch_param_set_buffer(&params, phyaddr_0, phyaddr_1);
	ipu_ch_param_set_rotation(&params, rot_mode);

	spin_lock_irqsave(&ipu->lock, flags);

	ipu_ग_लिखो_param_mem(dma_param_addr(channel), (uपूर्णांक32_t *)&params, 10);

	reg = idmac_पढ़ो_ipureg(ipu, IPU_CHA_DB_MODE_SEL);

	अगर (phyaddr_1)
		reg |= 1UL << channel;
	अन्यथा
		reg &= ~(1UL << channel);

	idmac_ग_लिखो_ipureg(ipu, reg, IPU_CHA_DB_MODE_SEL);

	ichan->status = IPU_CHANNEL_READY;

	spin_unlock_irqrestore(&ipu->lock, flags);

	वापस 0;
पूर्ण

/**
 * ipu_select_buffer() - mark a channel's buffer as पढ़ोy.
 * @channel:	channel ID.
 * @buffer_n:	buffer number to mark पढ़ोy.
 */
अटल व्योम ipu_select_buffer(क्रमागत ipu_channel channel, पूर्णांक buffer_n)
अणु
	/* No locking - this is a ग_लिखो-one-to-set रेजिस्टर, cleared by IPU */
	अगर (buffer_n == 0)
		/* Mark buffer 0 as पढ़ोy. */
		idmac_ग_लिखो_ipureg(&ipu_data, 1UL << channel, IPU_CHA_BUF0_RDY);
	अन्यथा
		/* Mark buffer 1 as पढ़ोy. */
		idmac_ग_लिखो_ipureg(&ipu_data, 1UL << channel, IPU_CHA_BUF1_RDY);
पूर्ण

/**
 * ipu_update_channel_buffer() - update physical address of a channel buffer.
 * @ichan:	IDMAC channel.
 * @buffer_n:	buffer number to update.
 *		0 or 1 are the only valid values.
 * @phyaddr:	buffer physical address.
 */
/* Called under spin_lock(_irqsave)(&ichan->lock) */
अटल व्योम ipu_update_channel_buffer(काष्ठा idmac_channel *ichan,
				      पूर्णांक buffer_n, dma_addr_t phyaddr)
अणु
	क्रमागत ipu_channel channel = ichan->dma_chan.chan_id;
	uपूर्णांक32_t reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipu_data.lock, flags);

	अगर (buffer_n == 0) अणु
		reg = idmac_पढ़ो_ipureg(&ipu_data, IPU_CHA_BUF0_RDY);
		अगर (reg & (1UL << channel)) अणु
			ipu_ic_disable_task(&ipu_data, channel);
			ichan->status = IPU_CHANNEL_READY;
		पूर्ण

		/* 44.3.3.1.9 - Row Number 1 (WORD1, offset 0) */
		idmac_ग_लिखो_ipureg(&ipu_data, dma_param_addr(channel) +
				   0x0008UL, IPU_IMA_ADDR);
		idmac_ग_लिखो_ipureg(&ipu_data, phyaddr, IPU_IMA_DATA);
	पूर्ण अन्यथा अणु
		reg = idmac_पढ़ो_ipureg(&ipu_data, IPU_CHA_BUF1_RDY);
		अगर (reg & (1UL << channel)) अणु
			ipu_ic_disable_task(&ipu_data, channel);
			ichan->status = IPU_CHANNEL_READY;
		पूर्ण

		/* Check अगर द्विगुन-buffering is alपढ़ोy enabled */
		reg = idmac_पढ़ो_ipureg(&ipu_data, IPU_CHA_DB_MODE_SEL);

		अगर (!(reg & (1UL << channel)))
			idmac_ग_लिखो_ipureg(&ipu_data, reg | (1UL << channel),
					   IPU_CHA_DB_MODE_SEL);

		/* 44.3.3.1.9 - Row Number 1 (WORD1, offset 1) */
		idmac_ग_लिखो_ipureg(&ipu_data, dma_param_addr(channel) +
				   0x0009UL, IPU_IMA_ADDR);
		idmac_ग_लिखो_ipureg(&ipu_data, phyaddr, IPU_IMA_DATA);
	पूर्ण

	spin_unlock_irqrestore(&ipu_data.lock, flags);
पूर्ण

/* Called under spin_lock_irqsave(&ichan->lock) */
अटल पूर्णांक ipu_submit_buffer(काष्ठा idmac_channel *ichan,
	काष्ठा idmac_tx_desc *desc, काष्ठा scatterlist *sg, पूर्णांक buf_idx)
अणु
	अचिन्हित पूर्णांक chan_id = ichan->dma_chan.chan_id;
	काष्ठा device *dev = &ichan->dma_chan.dev->device;

	अगर (async_tx_test_ack(&desc->txd))
		वापस -EINTR;

	/*
	 * On first invocation this shouldn't be necessary, the call to
	 * ipu_init_channel_buffer() above will set addresses क्रम us, so we
	 * could make it conditional on status >= IPU_CHANNEL_ENABLED, but
	 * करोing it again shouldn't hurt either.
	 */
	ipu_update_channel_buffer(ichan, buf_idx, sg_dma_address(sg));

	ipu_select_buffer(chan_id, buf_idx);
	dev_dbg(dev, "Updated sg %p on channel 0x%x buffer %d\n",
		sg, chan_id, buf_idx);

	वापस 0;
पूर्ण

/* Called under spin_lock_irqsave(&ichan->lock) */
अटल पूर्णांक ipu_submit_channel_buffers(काष्ठा idmac_channel *ichan,
				      काष्ठा idmac_tx_desc *desc)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i, ret = 0;

	क्रम (i = 0, sg = desc->sg; i < 2 && sg; i++) अणु
		अगर (!ichan->sg[i]) अणु
			ichan->sg[i] = sg;

			ret = ipu_submit_buffer(ichan, desc, sg, i);
			अगर (ret < 0)
				वापस ret;

			sg = sg_next(sg);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल dma_cookie_t idmac_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा idmac_tx_desc *desc = to_tx_desc(tx);
	काष्ठा idmac_channel *ichan = to_idmac_chan(tx->chan);
	काष्ठा idmac *idmac = to_idmac(tx->chan->device);
	काष्ठा ipu *ipu = to_ipu(idmac);
	काष्ठा device *dev = &ichan->dma_chan.dev->device;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Sanity check */
	अगर (!list_empty(&desc->list)) अणु
		/* The descriptor करोesn't beदीर्घ to client */
		dev_err(dev, "Descriptor %p not prepared!\n", tx);
		वापस -EBUSY;
	पूर्ण

	mutex_lock(&ichan->chan_mutex);

	async_tx_clear_ack(tx);

	अगर (ichan->status < IPU_CHANNEL_READY) अणु
		काष्ठा idmac_video_param *video = &ichan->params.video;
		/*
		 * Initial buffer assignment - the first two sg-entries from
		 * the descriptor will end up in the IDMAC buffers
		 */
		dma_addr_t dma_1 = sg_is_last(desc->sg) ? 0 :
			sg_dma_address(&desc->sg[1]);

		WARN_ON(ichan->sg[0] || ichan->sg[1]);

		cookie = ipu_init_channel_buffer(ichan,
						 video->out_pixel_fmt,
						 video->out_width,
						 video->out_height,
						 video->out_stride,
						 IPU_ROTATE_NONE,
						 sg_dma_address(&desc->sg[0]),
						 dma_1);
		अगर (cookie < 0)
			जाओ out;
	पूर्ण

	dev_dbg(dev, "Submitting sg %p\n", &desc->sg[0]);

	cookie = dma_cookie_assign(tx);

	/* ipu->lock can be taken under ichan->lock, but not v.v. */
	spin_lock_irqsave(&ichan->lock, flags);

	list_add_tail(&desc->list, &ichan->queue);
	/* submit_buffers() atomically verअगरies and fills empty sg slots */
	ret = ipu_submit_channel_buffers(ichan, desc);

	spin_unlock_irqrestore(&ichan->lock, flags);

	अगर (ret < 0) अणु
		cookie = ret;
		जाओ dequeue;
	पूर्ण

	अगर (ichan->status < IPU_CHANNEL_ENABLED) अणु
		ret = ipu_enable_channel(idmac, ichan);
		अगर (ret < 0) अणु
			cookie = ret;
			जाओ dequeue;
		पूर्ण
	पूर्ण

	dump_idmac_reg(ipu);

dequeue:
	अगर (cookie < 0) अणु
		spin_lock_irqsave(&ichan->lock, flags);
		list_del_init(&desc->list);
		spin_unlock_irqrestore(&ichan->lock, flags);
		tx->cookie = cookie;
		ichan->dma_chan.cookie = cookie;
	पूर्ण

out:
	mutex_unlock(&ichan->chan_mutex);

	वापस cookie;
पूर्ण

/* Called with ichan->chan_mutex held */
अटल पूर्णांक idmac_desc_alloc(काष्ठा idmac_channel *ichan, पूर्णांक n)
अणु
	काष्ठा idmac_tx_desc *desc =
		vदो_स्मृति(array_size(n, माप(काष्ठा idmac_tx_desc)));
	काष्ठा idmac *idmac = to_idmac(ichan->dma_chan.device);

	अगर (!desc)
		वापस -ENOMEM;

	/* No पूर्णांकerrupts, just disable the tasklet क्रम a moment */
	tasklet_disable(&to_ipu(idmac)->tasklet);

	ichan->n_tx_desc = n;
	ichan->desc = desc;
	INIT_LIST_HEAD(&ichan->queue);
	INIT_LIST_HEAD(&ichan->मुक्त_list);

	जबतक (n--) अणु
		काष्ठा dma_async_tx_descriptor *txd = &desc->txd;

		स_रखो(txd, 0, माप(*txd));
		dma_async_tx_descriptor_init(txd, &ichan->dma_chan);
		txd->tx_submit		= idmac_tx_submit;

		list_add(&desc->list, &ichan->मुक्त_list);

		desc++;
	पूर्ण

	tasklet_enable(&to_ipu(idmac)->tasklet);

	वापस 0;
पूर्ण

/**
 * ipu_init_channel() - initialize an IPU channel.
 * @idmac:	IPU DMAC context.
 * @ichan:	poपूर्णांकer to the channel object.
 * @वापस      0 on success or negative error code on failure.
 */
अटल पूर्णांक ipu_init_channel(काष्ठा idmac *idmac, काष्ठा idmac_channel *ichan)
अणु
	जोड़ ipu_channel_param *params = &ichan->params;
	uपूर्णांक32_t ipu_conf;
	क्रमागत ipu_channel channel = ichan->dma_chan.chan_id;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t reg;
	काष्ठा ipu *ipu = to_ipu(idmac);
	पूर्णांक ret = 0, n_desc = 0;

	dev_dbg(ipu->dev, "init channel = %d\n", channel);

	अगर (channel != IDMAC_SDC_0 && channel != IDMAC_SDC_1 &&
	    channel != IDMAC_IC_7)
		वापस -EINVAL;

	spin_lock_irqsave(&ipu->lock, flags);

	चयन (channel) अणु
	हाल IDMAC_IC_7:
		n_desc = 16;
		reg = idmac_पढ़ो_icreg(ipu, IC_CONF);
		idmac_ग_लिखो_icreg(ipu, reg & ~IC_CONF_CSI_MEM_WR_EN, IC_CONF);
		अवरोध;
	हाल IDMAC_IC_0:
		n_desc = 16;
		reg = idmac_पढ़ो_ipureg(ipu, IPU_FS_PROC_FLOW);
		idmac_ग_लिखो_ipureg(ipu, reg & ~FS_ENC_IN_VALID, IPU_FS_PROC_FLOW);
		ret = ipu_ic_init_prpenc(ipu, params, true);
		अवरोध;
	हाल IDMAC_SDC_0:
	हाल IDMAC_SDC_1:
		n_desc = 4;
	शेष:
		अवरोध;
	पूर्ण

	ipu->channel_init_mask |= 1L << channel;

	/* Enable IPU sub module */
	ipu_conf = idmac_पढ़ो_ipureg(ipu, IPU_CONF) |
		ipu_channel_conf_mask(channel);
	idmac_ग_लिखो_ipureg(ipu, ipu_conf, IPU_CONF);

	spin_unlock_irqrestore(&ipu->lock, flags);

	अगर (n_desc && !ichan->desc)
		ret = idmac_desc_alloc(ichan, n_desc);

	dump_idmac_reg(ipu);

	वापस ret;
पूर्ण

/**
 * ipu_uninit_channel() - uninitialize an IPU channel.
 * @idmac:	IPU DMAC context.
 * @ichan:	poपूर्णांकer to the channel object.
 */
अटल व्योम ipu_uninit_channel(काष्ठा idmac *idmac, काष्ठा idmac_channel *ichan)
अणु
	क्रमागत ipu_channel channel = ichan->dma_chan.chan_id;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t reg;
	अचिन्हित दीर्घ chan_mask = 1UL << channel;
	uपूर्णांक32_t ipu_conf;
	काष्ठा ipu *ipu = to_ipu(idmac);

	spin_lock_irqsave(&ipu->lock, flags);

	अगर (!(ipu->channel_init_mask & chan_mask)) अणु
		dev_err(ipu->dev, "Channel already uninitialized %d\n",
			channel);
		spin_unlock_irqrestore(&ipu->lock, flags);
		वापस;
	पूर्ण

	/* Reset the द्विगुन buffer */
	reg = idmac_पढ़ो_ipureg(ipu, IPU_CHA_DB_MODE_SEL);
	idmac_ग_लिखो_ipureg(ipu, reg & ~chan_mask, IPU_CHA_DB_MODE_SEL);

	ichan->sec_chan_en = false;

	चयन (channel) अणु
	हाल IDMAC_IC_7:
		reg = idmac_पढ़ो_icreg(ipu, IC_CONF);
		idmac_ग_लिखो_icreg(ipu, reg & ~(IC_CONF_RWS_EN | IC_CONF_PRPENC_EN),
			     IC_CONF);
		अवरोध;
	हाल IDMAC_IC_0:
		reg = idmac_पढ़ो_icreg(ipu, IC_CONF);
		idmac_ग_लिखो_icreg(ipu, reg & ~(IC_CONF_PRPENC_EN | IC_CONF_PRPENC_CSC1),
				  IC_CONF);
		अवरोध;
	हाल IDMAC_SDC_0:
	हाल IDMAC_SDC_1:
	शेष:
		अवरोध;
	पूर्ण

	ipu->channel_init_mask &= ~(1L << channel);

	ipu_conf = idmac_पढ़ो_ipureg(ipu, IPU_CONF) &
		~ipu_channel_conf_mask(channel);
	idmac_ग_लिखो_ipureg(ipu, ipu_conf, IPU_CONF);

	spin_unlock_irqrestore(&ipu->lock, flags);

	ichan->n_tx_desc = 0;
	vमुक्त(ichan->desc);
	ichan->desc = शून्य;
पूर्ण

/**
 * ipu_disable_channel() - disable an IPU channel.
 * @idmac:		IPU DMAC context.
 * @ichan:		channel object poपूर्णांकer.
 * @रुको_क्रम_stop:	flag to set whether to रुको क्रम channel end of frame or
 *			वापस immediately.
 * @वापस:		0 on success or negative error code on failure.
 */
अटल पूर्णांक ipu_disable_channel(काष्ठा idmac *idmac, काष्ठा idmac_channel *ichan,
			       bool रुको_क्रम_stop)
अणु
	क्रमागत ipu_channel channel = ichan->dma_chan.chan_id;
	काष्ठा ipu *ipu = to_ipu(idmac);
	uपूर्णांक32_t reg;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ chan_mask = 1UL << channel;
	अचिन्हित पूर्णांक समयout;

	अगर (रुको_क्रम_stop && channel != IDMAC_SDC_1 && channel != IDMAC_SDC_0) अणु
		समयout = 40;
		/* This रुकोing always fails. Related to spurious irq problem */
		जबतक ((idmac_पढ़ो_icreg(ipu, IDMAC_CHA_BUSY) & chan_mask) ||
		       (ipu_channel_status(ipu, channel) == TASK_STAT_ACTIVE)) अणु
			समयout--;
			msleep(10);

			अगर (!समयout) अणु
				dev_dbg(ipu->dev,
					"Warning: timeout waiting for channel %u to "
					"stop: buf0_rdy = 0x%08X, buf1_rdy = 0x%08X, "
					"busy = 0x%08X, tstat = 0x%08X\n", channel,
					idmac_पढ़ो_ipureg(ipu, IPU_CHA_BUF0_RDY),
					idmac_पढ़ो_ipureg(ipu, IPU_CHA_BUF1_RDY),
					idmac_पढ़ो_icreg(ipu, IDMAC_CHA_BUSY),
					idmac_पढ़ो_ipureg(ipu, IPU_TASKS_STAT));
				अवरोध;
			पूर्ण
		पूर्ण
		dev_dbg(ipu->dev, "timeout = %d * 10ms\n", 40 - समयout);
	पूर्ण
	/* SDC BG and FG must be disabled beक्रमe DMA is disabled */
	अगर (रुको_क्रम_stop && (channel == IDMAC_SDC_0 ||
			      channel == IDMAC_SDC_1)) अणु
		क्रम (समयout = 5;
		     समयout && !ipu_irq_status(ichan->eof_irq); समयout--)
			msleep(5);
	पूर्ण

	spin_lock_irqsave(&ipu->lock, flags);

	/* Disable IC task */
	ipu_ic_disable_task(ipu, channel);

	/* Disable DMA channel(s) */
	reg = idmac_पढ़ो_icreg(ipu, IDMAC_CHA_EN);
	idmac_ग_लिखो_icreg(ipu, reg & ~chan_mask, IDMAC_CHA_EN);

	spin_unlock_irqrestore(&ipu->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा scatterlist *idmac_sg_next(काष्ठा idmac_channel *ichan,
	काष्ठा idmac_tx_desc **desc, काष्ठा scatterlist *sg)
अणु
	काष्ठा scatterlist *sgnew = sg ? sg_next(sg) : शून्य;

	अगर (sgnew)
		/* next sg-element in this list */
		वापस sgnew;

	अगर ((*desc)->list.next == &ichan->queue)
		/* No more descriptors on the queue */
		वापस शून्य;

	/* Fetch next descriptor */
	*desc = list_entry((*desc)->list.next, काष्ठा idmac_tx_desc, list);
	वापस (*desc)->sg;
पूर्ण

/*
 * We have several possibilities here:
 * current BUF		next BUF
 *
 * not last sg		next not last sg
 * not last sg		next last sg
 * last sg		first sg from next descriptor
 * last sg		शून्य
 *
 * Besides, the descriptor queue might be empty or not. We process all these
 * हालs carefully.
 */
अटल irqवापस_t idmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा idmac_channel *ichan = dev_id;
	काष्ठा device *dev = &ichan->dma_chan.dev->device;
	अचिन्हित पूर्णांक chan_id = ichan->dma_chan.chan_id;
	काष्ठा scatterlist **sg, *sgnext, *sgnew = शून्य;
	/* Next transfer descriptor */
	काष्ठा idmac_tx_desc *desc, *descnew;
	bool करोne = false;
	u32 पढ़ोy0, पढ़ोy1, curbuf, err;
	काष्ठा dmaengine_desc_callback cb;

	/* IDMAC has cleared the respective BUFx_RDY bit, we manage the buffer */

	dev_dbg(dev, "IDMAC irq %d, buf %d\n", irq, ichan->active_buffer);

	spin_lock(&ipu_data.lock);

	पढ़ोy0	= idmac_पढ़ो_ipureg(&ipu_data, IPU_CHA_BUF0_RDY);
	पढ़ोy1	= idmac_पढ़ो_ipureg(&ipu_data, IPU_CHA_BUF1_RDY);
	curbuf	= idmac_पढ़ो_ipureg(&ipu_data, IPU_CHA_CUR_BUF);
	err	= idmac_पढ़ो_ipureg(&ipu_data, IPU_INT_STAT_4);

	अगर (err & (1 << chan_id)) अणु
		idmac_ग_लिखो_ipureg(&ipu_data, 1 << chan_id, IPU_INT_STAT_4);
		spin_unlock(&ipu_data.lock);
		/*
		 * Doing this
		 * ichan->sg[0] = ichan->sg[1] = शून्य;
		 * you can क्रमce channel re-enable on the next tx_submit(), but
		 * this is dirty - think about descriptors with multiple
		 * sg elements.
		 */
		dev_warn(dev, "NFB4EOF on channel %d, ready %x, %x, cur %x\n",
			 chan_id, पढ़ोy0, पढ़ोy1, curbuf);
		वापस IRQ_HANDLED;
	पूर्ण
	spin_unlock(&ipu_data.lock);

	/* Other पूर्णांकerrupts करो not पूर्णांकerfere with this channel */
	spin_lock(&ichan->lock);
	अगर (unlikely((ichan->active_buffer && (पढ़ोy1 >> chan_id) & 1) ||
		     (!ichan->active_buffer && (पढ़ोy0 >> chan_id) & 1)
		     )) अणु
		spin_unlock(&ichan->lock);
		dev_dbg(dev,
			"IRQ with active buffer still ready on channel %x, "
			"active %d, ready %x, %x!\n", chan_id,
			ichan->active_buffer, पढ़ोy0, पढ़ोy1);
		वापस IRQ_NONE;
	पूर्ण

	अगर (unlikely(list_empty(&ichan->queue))) अणु
		ichan->sg[ichan->active_buffer] = शून्य;
		spin_unlock(&ichan->lock);
		dev_err(dev,
			"IRQ without queued buffers on channel %x, active %d, "
			"ready %x, %x!\n", chan_id,
			ichan->active_buffer, पढ़ोy0, पढ़ोy1);
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * active_buffer is a software flag, it shows which buffer we are
	 * currently expecting back from the hardware, IDMAC should be
	 * processing the other buffer alपढ़ोy
	 */
	sg = &ichan->sg[ichan->active_buffer];
	sgnext = ichan->sg[!ichan->active_buffer];

	अगर (!*sg) अणु
		spin_unlock(&ichan->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	desc = list_entry(ichan->queue.next, काष्ठा idmac_tx_desc, list);
	descnew = desc;

	dev_dbg(dev, "IDMAC irq %d, dma %#llx, next dma %#llx, current %d, curbuf %#x\n",
		irq, (u64)sg_dma_address(*sg),
		sgnext ? (u64)sg_dma_address(sgnext) : 0,
		ichan->active_buffer, curbuf);

	/* Find the descriptor of sgnext */
	sgnew = idmac_sg_next(ichan, &descnew, *sg);
	अगर (sgnext != sgnew)
		dev_err(dev, "Submitted buffer %p, next buffer %p\n", sgnext, sgnew);

	/*
	 * अगर sgnext == शून्य sg must be the last element in a scatterlist and
	 * queue must be empty
	 */
	अगर (unlikely(!sgnext)) अणु
		अगर (!WARN_ON(sg_next(*sg)))
			dev_dbg(dev, "Underrun on channel %x\n", chan_id);
		ichan->sg[!ichan->active_buffer] = sgnew;

		अगर (unlikely(sgnew)) अणु
			ipu_submit_buffer(ichan, descnew, sgnew, !ichan->active_buffer);
		पूर्ण अन्यथा अणु
			spin_lock(&ipu_data.lock);
			ipu_ic_disable_task(&ipu_data, chan_id);
			spin_unlock(&ipu_data.lock);
			ichan->status = IPU_CHANNEL_READY;
			/* Continue to check क्रम complete descriptor */
		पूर्ण
	पूर्ण

	/* Calculate and submit the next sg element */
	sgnew = idmac_sg_next(ichan, &descnew, sgnew);

	अगर (unlikely(!sg_next(*sg)) || !sgnext) अणु
		/*
		 * Last element in scatterlist करोne, हटाओ from the queue,
		 * _init क्रम debugging
		 */
		list_del_init(&desc->list);
		करोne = true;
	पूर्ण

	*sg = sgnew;

	अगर (likely(sgnew) &&
	    ipu_submit_buffer(ichan, descnew, sgnew, ichan->active_buffer) < 0) अणु
		dmaengine_desc_get_callback(&descnew->txd, &cb);

		list_del_init(&descnew->list);
		spin_unlock(&ichan->lock);

		dmaengine_desc_callback_invoke(&cb, शून्य);
		spin_lock(&ichan->lock);
	पूर्ण

	/* Flip the active buffer - even अगर update above failed */
	ichan->active_buffer = !ichan->active_buffer;
	अगर (करोne)
		dma_cookie_complete(&desc->txd);

	dmaengine_desc_get_callback(&desc->txd, &cb);

	spin_unlock(&ichan->lock);

	अगर (करोne && (desc->txd.flags & DMA_PREP_INTERRUPT))
		dmaengine_desc_callback_invoke(&cb, शून्य);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ipu_gc_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ipu *ipu = from_tasklet(ipu, t, tasklet);
	पूर्णांक i;

	क्रम (i = 0; i < IPU_CHANNELS_NUM; i++) अणु
		काष्ठा idmac_channel *ichan = ipu->channel + i;
		काष्ठा idmac_tx_desc *desc;
		अचिन्हित दीर्घ flags;
		काष्ठा scatterlist *sg;
		पूर्णांक j, k;

		क्रम (j = 0; j < ichan->n_tx_desc; j++) अणु
			desc = ichan->desc + j;
			spin_lock_irqsave(&ichan->lock, flags);
			अगर (async_tx_test_ack(&desc->txd)) अणु
				list_move(&desc->list, &ichan->मुक्त_list);
				क्रम_each_sg(desc->sg, sg, desc->sg_len, k) अणु
					अगर (ichan->sg[0] == sg)
						ichan->sg[0] = शून्य;
					अन्यथा अगर (ichan->sg[1] == sg)
						ichan->sg[1] = शून्य;
				पूर्ण
				async_tx_clear_ack(&desc->txd);
			पूर्ण
			spin_unlock_irqrestore(&ichan->lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

/* Allocate and initialise a transfer descriptor. */
अटल काष्ठा dma_async_tx_descriptor *idmac_prep_slave_sg(काष्ठा dma_chan *chan,
		काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
		क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ tx_flags,
		व्योम *context)
अणु
	काष्ठा idmac_channel *ichan = to_idmac_chan(chan);
	काष्ठा idmac_tx_desc *desc = शून्य;
	काष्ठा dma_async_tx_descriptor *txd = शून्य;
	अचिन्हित दीर्घ flags;

	/* We only can handle these three channels so far */
	अगर (chan->chan_id != IDMAC_SDC_0 && chan->chan_id != IDMAC_SDC_1 &&
	    chan->chan_id != IDMAC_IC_7)
		वापस शून्य;

	अगर (!is_slave_direction(direction)) अणु
		dev_err(chan->device->dev, "Invalid DMA direction %d!\n", direction);
		वापस शून्य;
	पूर्ण

	mutex_lock(&ichan->chan_mutex);

	spin_lock_irqsave(&ichan->lock, flags);
	अगर (!list_empty(&ichan->मुक्त_list)) अणु
		desc = list_entry(ichan->मुक्त_list.next,
				  काष्ठा idmac_tx_desc, list);

		list_del_init(&desc->list);

		desc->sg_len	= sg_len;
		desc->sg	= sgl;
		txd		= &desc->txd;
		txd->flags	= tx_flags;
	पूर्ण
	spin_unlock_irqrestore(&ichan->lock, flags);

	mutex_unlock(&ichan->chan_mutex);

	tasklet_schedule(&to_ipu(to_idmac(chan->device))->tasklet);

	वापस txd;
पूर्ण

/* Re-select the current buffer and re-activate the channel */
अटल व्योम idmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा idmac_channel *ichan = to_idmac_chan(chan);
	काष्ठा idmac *idmac = to_idmac(chan->device);
	काष्ठा ipu *ipu = to_ipu(idmac);
	अचिन्हित दीर्घ flags;

	/* This is not always needed, but करोesn't hurt either */
	spin_lock_irqsave(&ipu->lock, flags);
	ipu_select_buffer(chan->chan_id, ichan->active_buffer);
	spin_unlock_irqrestore(&ipu->lock, flags);

	/*
	 * Might need to perक्रमm some parts of initialisation from
	 * ipu_enable_channel(), but not all, we करो not want to reset to buffer
	 * 0, करोn't need to set priority again either, but re-enabling the task
	 * and the channel might be a good idea.
	 */
पूर्ण

अटल पूर्णांक idmac_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा idmac_channel *ichan = to_idmac_chan(chan);
	काष्ठा idmac *idmac = to_idmac(chan->device);
	काष्ठा ipu *ipu = to_ipu(idmac);
	काष्ठा list_head *list, *पंचांगp;
	अचिन्हित दीर्घ flags;

	mutex_lock(&ichan->chan_mutex);

	spin_lock_irqsave(&ipu->lock, flags);
	ipu_ic_disable_task(ipu, chan->chan_id);

	/* Return all descriptors पूर्णांकo "prepared" state */
	list_क्रम_each_safe(list, पंचांगp, &ichan->queue)
		list_del_init(list);

	ichan->sg[0] = शून्य;
	ichan->sg[1] = शून्य;

	spin_unlock_irqrestore(&ipu->lock, flags);

	ichan->status = IPU_CHANNEL_INITIALIZED;

	mutex_unlock(&ichan->chan_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __idmac_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा idmac_channel *ichan = to_idmac_chan(chan);
	काष्ठा idmac *idmac = to_idmac(chan->device);
	काष्ठा ipu *ipu = to_ipu(idmac);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	ipu_disable_channel(idmac, ichan,
			    ichan->status >= IPU_CHANNEL_ENABLED);

	tasklet_disable(&ipu->tasklet);

	/* ichan->queue is modअगरied in ISR, have to spinlock */
	spin_lock_irqsave(&ichan->lock, flags);
	list_splice_init(&ichan->queue, &ichan->मुक्त_list);

	अगर (ichan->desc)
		क्रम (i = 0; i < ichan->n_tx_desc; i++) अणु
			काष्ठा idmac_tx_desc *desc = ichan->desc + i;
			अगर (list_empty(&desc->list))
				/* Descriptor was prepared, but not submitted */
				list_add(&desc->list, &ichan->मुक्त_list);

			async_tx_clear_ack(&desc->txd);
		पूर्ण

	ichan->sg[0] = शून्य;
	ichan->sg[1] = शून्य;
	spin_unlock_irqrestore(&ichan->lock, flags);

	tasklet_enable(&ipu->tasklet);

	ichan->status = IPU_CHANNEL_INITIALIZED;

	वापस 0;
पूर्ण

अटल पूर्णांक idmac_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा idmac_channel *ichan = to_idmac_chan(chan);
	पूर्णांक ret;

	mutex_lock(&ichan->chan_mutex);

	ret = __idmac_terminate_all(chan);

	mutex_unlock(&ichan->chan_mutex);

	वापस ret;
पूर्ण

#अगर_घोषित DEBUG
अटल irqवापस_t ic_sof_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा idmac_channel *ichan = dev_id;
	prपूर्णांकk(KERN_DEBUG "Got SOF IRQ %d on Channel %d\n",
	       irq, ichan->dma_chan.chan_id);
	disable_irq_nosync(irq);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ic_eof_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा idmac_channel *ichan = dev_id;
	prपूर्णांकk(KERN_DEBUG "Got EOF IRQ %d on Channel %d\n",
	       irq, ichan->dma_chan.chan_id);
	disable_irq_nosync(irq);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ic_sof = -EINVAL, ic_eof = -EINVAL;
#पूर्ण_अगर

अटल पूर्णांक idmac_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा idmac_channel *ichan = to_idmac_chan(chan);
	काष्ठा idmac *idmac = to_idmac(chan->device);
	पूर्णांक ret;

	/* dmaengine.c now guarantees to only offer मुक्त channels */
	BUG_ON(chan->client_count > 1);
	WARN_ON(ichan->status != IPU_CHANNEL_FREE);

	dma_cookie_init(chan);

	ret = ipu_irq_map(chan->chan_id);
	अगर (ret < 0)
		जाओ eimap;

	ichan->eof_irq = ret;

	/*
	 * Important to first disable the channel, because maybe someone
	 * used it beक्रमe us, e.g., the bootloader
	 */
	ipu_disable_channel(idmac, ichan, true);

	ret = ipu_init_channel(idmac, ichan);
	अगर (ret < 0)
		जाओ eichan;

	ret = request_irq(ichan->eof_irq, idmac_पूर्णांकerrupt, 0,
			  ichan->eof_name, ichan);
	अगर (ret < 0)
		जाओ erirq;

#अगर_घोषित DEBUG
	अगर (chan->chan_id == IDMAC_IC_7) अणु
		ic_sof = ipu_irq_map(69);
		अगर (ic_sof > 0) अणु
			ret = request_irq(ic_sof, ic_sof_irq, 0, "IC SOF", ichan);
			अगर (ret)
				dev_err(&chan->dev->device, "request irq failed for IC SOF");
		पूर्ण
		ic_eof = ipu_irq_map(70);
		अगर (ic_eof > 0) अणु
			ret = request_irq(ic_eof, ic_eof_irq, 0, "IC EOF", ichan);
			अगर (ret)
				dev_err(&chan->dev->device, "request irq failed for IC EOF");
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	ichan->status = IPU_CHANNEL_INITIALIZED;

	dev_dbg(&chan->dev->device, "Found channel 0x%x, irq %d\n",
		chan->chan_id, ichan->eof_irq);

	वापस ret;

erirq:
	ipu_uninit_channel(idmac, ichan);
eichan:
	ipu_irq_unmap(chan->chan_id);
eimap:
	वापस ret;
पूर्ण

अटल व्योम idmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा idmac_channel *ichan = to_idmac_chan(chan);
	काष्ठा idmac *idmac = to_idmac(chan->device);

	mutex_lock(&ichan->chan_mutex);

	__idmac_terminate_all(chan);

	अगर (ichan->status > IPU_CHANNEL_FREE) अणु
#अगर_घोषित DEBUG
		अगर (chan->chan_id == IDMAC_IC_7) अणु
			अगर (ic_sof > 0) अणु
				मुक्त_irq(ic_sof, ichan);
				ipu_irq_unmap(69);
				ic_sof = -EINVAL;
			पूर्ण
			अगर (ic_eof > 0) अणु
				मुक्त_irq(ic_eof, ichan);
				ipu_irq_unmap(70);
				ic_eof = -EINVAL;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		मुक्त_irq(ichan->eof_irq, ichan);
		ipu_irq_unmap(chan->chan_id);
	पूर्ण

	ichan->status = IPU_CHANNEL_FREE;

	ipu_uninit_channel(idmac, ichan);

	mutex_unlock(&ichan->chan_mutex);

	tasklet_schedule(&to_ipu(idmac)->tasklet);
पूर्ण

अटल क्रमागत dma_status idmac_tx_status(काष्ठा dma_chan *chan,
		       dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

अटल पूर्णांक __init ipu_idmac_init(काष्ठा ipu *ipu)
अणु
	काष्ठा idmac *idmac = &ipu->idmac;
	काष्ठा dma_device *dma = &idmac->dma;
	पूर्णांक i;

	dma_cap_set(DMA_SLAVE, dma->cap_mask);
	dma_cap_set(DMA_PRIVATE, dma->cap_mask);

	/* Compulsory common fields */
	dma->dev				= ipu->dev;
	dma->device_alloc_chan_resources	= idmac_alloc_chan_resources;
	dma->device_मुक्त_chan_resources		= idmac_मुक्त_chan_resources;
	dma->device_tx_status			= idmac_tx_status;
	dma->device_issue_pending		= idmac_issue_pending;

	/* Compulsory क्रम DMA_SLAVE fields */
	dma->device_prep_slave_sg		= idmac_prep_slave_sg;
	dma->device_छोड़ो			= idmac_छोड़ो;
	dma->device_terminate_all		= idmac_terminate_all;

	INIT_LIST_HEAD(&dma->channels);
	क्रम (i = 0; i < IPU_CHANNELS_NUM; i++) अणु
		काष्ठा idmac_channel *ichan = ipu->channel + i;
		काष्ठा dma_chan *dma_chan = &ichan->dma_chan;

		spin_lock_init(&ichan->lock);
		mutex_init(&ichan->chan_mutex);

		ichan->status		= IPU_CHANNEL_FREE;
		ichan->sec_chan_en	= false;
		snम_लिखो(ichan->eof_name, माप(ichan->eof_name), "IDMAC EOF %d", i);

		dma_chan->device	= &idmac->dma;
		dma_cookie_init(dma_chan);
		dma_chan->chan_id	= i;
		list_add_tail(&dma_chan->device_node, &dma->channels);
	पूर्ण

	idmac_ग_लिखो_icreg(ipu, 0x00000070, IDMAC_CONF);

	वापस dma_async_device_रेजिस्टर(&idmac->dma);
पूर्ण

अटल व्योम ipu_idmac_निकास(काष्ठा ipu *ipu)
अणु
	पूर्णांक i;
	काष्ठा idmac *idmac = &ipu->idmac;

	क्रम (i = 0; i < IPU_CHANNELS_NUM; i++) अणु
		काष्ठा idmac_channel *ichan = ipu->channel + i;

		idmac_terminate_all(&ichan->dma_chan);
	पूर्ण

	dma_async_device_unरेजिस्टर(&idmac->dma);
पूर्ण

/*****************************************************************************
 * IPU common probe / हटाओ
 */

अटल पूर्णांक __init ipu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *mem_ipu, *mem_ic;
	पूर्णांक ret;

	spin_lock_init(&ipu_data.lock);

	mem_ipu	= platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mem_ic	= platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!mem_ipu || !mem_ic)
		वापस -EINVAL;

	ipu_data.dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, &ipu_data);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_noirq;

	ipu_data.irq_fn = ret;
	ret = platक्रमm_get_irq(pdev, 1);
	अगर (ret < 0)
		जाओ err_noirq;

	ipu_data.irq_err = ret;

	dev_dbg(&pdev->dev, "fn irq %u, err irq %u\n",
		ipu_data.irq_fn, ipu_data.irq_err);

	/* Remap IPU common रेजिस्टरs */
	ipu_data.reg_ipu = ioremap(mem_ipu->start, resource_size(mem_ipu));
	अगर (!ipu_data.reg_ipu) अणु
		ret = -ENOMEM;
		जाओ err_ioremap_ipu;
	पूर्ण

	/* Remap Image Converter and Image DMA Controller रेजिस्टरs */
	ipu_data.reg_ic = ioremap(mem_ic->start, resource_size(mem_ic));
	अगर (!ipu_data.reg_ic) अणु
		ret = -ENOMEM;
		जाओ err_ioremap_ic;
	पूर्ण

	/* Get IPU घड़ी */
	ipu_data.ipu_clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ipu_data.ipu_clk)) अणु
		ret = PTR_ERR(ipu_data.ipu_clk);
		जाओ err_clk_get;
	पूर्ण

	/* Make sure IPU HSP घड़ी is running */
	clk_prepare_enable(ipu_data.ipu_clk);

	/* Disable all पूर्णांकerrupts */
	idmac_ग_लिखो_ipureg(&ipu_data, 0, IPU_INT_CTRL_1);
	idmac_ग_लिखो_ipureg(&ipu_data, 0, IPU_INT_CTRL_2);
	idmac_ग_लिखो_ipureg(&ipu_data, 0, IPU_INT_CTRL_3);
	idmac_ग_लिखो_ipureg(&ipu_data, 0, IPU_INT_CTRL_4);
	idmac_ग_लिखो_ipureg(&ipu_data, 0, IPU_INT_CTRL_5);

	dev_dbg(&pdev->dev, "%s @ 0x%08lx, fn irq %u, err irq %u\n", pdev->name,
		(अचिन्हित दीर्घ)mem_ipu->start, ipu_data.irq_fn, ipu_data.irq_err);

	ret = ipu_irq_attach_irq(&ipu_data, pdev);
	अगर (ret < 0)
		जाओ err_attach_irq;

	/* Initialize DMA engine */
	ret = ipu_idmac_init(&ipu_data);
	अगर (ret < 0)
		जाओ err_idmac_init;

	tasklet_setup(&ipu_data.tasklet, ipu_gc_tasklet);

	ipu_data.dev = &pdev->dev;

	dev_dbg(ipu_data.dev, "IPU initialized\n");

	वापस 0;

err_idmac_init:
err_attach_irq:
	ipu_irq_detach_irq(&ipu_data, pdev);
	clk_disable_unprepare(ipu_data.ipu_clk);
	clk_put(ipu_data.ipu_clk);
err_clk_get:
	iounmap(ipu_data.reg_ic);
err_ioremap_ic:
	iounmap(ipu_data.reg_ipu);
err_ioremap_ipu:
err_noirq:
	dev_err(&pdev->dev, "Failed to probe IPU: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ipu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipu *ipu = platक्रमm_get_drvdata(pdev);

	ipu_idmac_निकास(ipu);
	ipu_irq_detach_irq(ipu, pdev);
	clk_disable_unprepare(ipu->ipu_clk);
	clk_put(ipu->ipu_clk);
	iounmap(ipu->reg_ic);
	iounmap(ipu->reg_ipu);
	tasklet_समाप्त(&ipu->tasklet);

	वापस 0;
पूर्ण

/*
 * We need two MEM resources - with IPU-common and Image Converter रेजिस्टरs,
 * including PF_CONF and IDMAC_* रेजिस्टरs, and two IRQs - function and error
 */
अटल काष्ठा platक्रमm_driver ipu_platक्रमm_driver = अणु
	.driver = अणु
		.name	= "ipu-core",
	पूर्ण,
	.हटाओ		= ipu_हटाओ,
पूर्ण;

अटल पूर्णांक __init ipu_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&ipu_platक्रमm_driver, ipu_probe);
पूर्ण
subsys_initcall(ipu_init);

MODULE_DESCRIPTION("IPU core driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Guennadi Liakhovetski <lg@denx.de>");
MODULE_ALIAS("platform:ipu-core");
