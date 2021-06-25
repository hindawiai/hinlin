<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Marvell camera core काष्ठाures.
 *
 * Copyright 2011 Jonathan Corbet corbet@lwn.net
 */
#अगर_अघोषित _MCAM_CORE_H
#घोषणा _MCAM_CORE_H

#समावेश <linux/list.h>
#समावेश <linux/clk-provider.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/videobuf2-v4l2.h>

/*
 * Create our own symbols क्रम the supported buffer modes, but, क्रम now,
 * base them entirely on which videobuf2 options have been selected.
 */
#अगर IS_ENABLED(CONFIG_VIDEOBUF2_VMALLOC)
#घोषणा MCAM_MODE_VMALLOC 1
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_VIDEOBUF2_DMA_CONTIG)
#घोषणा MCAM_MODE_DMA_CONTIG 1
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_VIDEOBUF2_DMA_SG)
#घोषणा MCAM_MODE_DMA_SG 1
#पूर्ण_अगर

#अगर !defined(MCAM_MODE_VMALLOC) && !defined(MCAM_MODE_DMA_CONTIG) && \
	!defined(MCAM_MODE_DMA_SG)
#त्रुटि One of the videobuf buffer modes must be selected in the config
#पूर्ण_अगर


क्रमागत mcam_state अणु
	S_NOTREADY,	/* Not yet initialized */
	S_IDLE,		/* Just hanging around */
	S_FLAKED,	/* Some sort of problem */
	S_STREAMING,	/* Streaming data */
	S_BUFWAIT	/* streaming requested but no buffers yet */
पूर्ण;
#घोषणा MAX_DMA_BUFS 3

/*
 * Dअगरferent platक्रमms work best with dअगरferent buffer modes, so we
 * let the platक्रमm pick.
 */
क्रमागत mcam_buffer_mode अणु
	B_vदो_स्मृति = 0,
	B_DMA_contig = 1,
	B_DMA_sg = 2
पूर्ण;

क्रमागत mcam_chip_id अणु
	MCAM_CAFE,
	MCAM_ARMADA610,
पूर्ण;

/*
 * Is a given buffer mode supported by the current kernel configuration?
 */
अटल अंतरभूत पूर्णांक mcam_buffer_mode_supported(क्रमागत mcam_buffer_mode mode)
अणु
	चयन (mode) अणु
#अगर_घोषित MCAM_MODE_VMALLOC
	हाल B_vदो_स्मृति:
#पूर्ण_अगर
#अगर_घोषित MCAM_MODE_DMA_CONTIG
	हाल B_DMA_contig:
#पूर्ण_अगर
#अगर_घोषित MCAM_MODE_DMA_SG
	हाल B_DMA_sg:
#पूर्ण_अगर
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Basic frame states
 */
काष्ठा mcam_frame_state अणु
	अचिन्हित पूर्णांक frames;
	अचिन्हित पूर्णांक singles;
	अचिन्हित पूर्णांक delivered;
पूर्ण;

#घोषणा NR_MCAM_CLK 3

/*
 * A description of one of our devices.
 * Locking: controlled by s_mutex.  Certain fields, however, require
 *          the dev_lock spinlock; they are marked as such by comments.
 *          dev_lock is also required क्रम access to device रेजिस्टरs.
 */
काष्ठा mcam_camera अणु
	/*
	 * These fields should be set by the platक्रमm code prior to
	 * calling mcam_रेजिस्टर().
	 */
	अचिन्हित अक्षर __iomem *regs;
	अचिन्हित regs_size; /* size in bytes of the रेजिस्टर space */
	spinlock_t dev_lock;
	काष्ठा device *dev; /* For messages, dma alloc */
	क्रमागत mcam_chip_id chip_id;
	क्रमागत mcam_buffer_mode buffer_mode;

	पूर्णांक mclk_src;	/* which घड़ी source the mclk derives from */
	पूर्णांक mclk_भाग;	/* Clock Divider Value क्रम MCLK */

	क्रमागत v4l2_mbus_type bus_type;
	/* MIPI support */
	/* The dphy config value, allocated in board file
	 * dphy[0]: DPHY3
	 * dphy[1]: DPHY5
	 * dphy[2]: DPHY6
	 */
	पूर्णांक *dphy;
	bool mipi_enabled;	/* flag whether mipi is enabled alपढ़ोy */
	पूर्णांक lane;			/* lane number */

	/* घड़ी tree support */
	काष्ठा clk *clk[NR_MCAM_CLK];
	काष्ठा clk_hw mclk_hw;
	काष्ठा clk *mclk;

	/*
	 * Callbacks from the core to the platक्रमm code.
	 */
	पूर्णांक (*plat_घातer_up) (काष्ठा mcam_camera *cam);
	व्योम (*plat_घातer_करोwn) (काष्ठा mcam_camera *cam);
	व्योम (*calc_dphy) (काष्ठा mcam_camera *cam);

	/*
	 * Everything below here is निजी to the mcam core and
	 * should not be touched by the platक्रमm code.
	 */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	क्रमागत mcam_state state;
	अचिन्हित दीर्घ flags;		/* Buffer status, मुख्यly (dev_lock) */

	काष्ठा mcam_frame_state frame_state;	/* Frame state counter */
	/*
	 * Subप्रणाली काष्ठाures.
	 */
	काष्ठा video_device vdev;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा v4l2_subdev *sensor;

	/* Videobuf2 stuff */
	काष्ठा vb2_queue vb_queue;
	काष्ठा list_head buffers;	/* Available frames */

	अचिन्हित पूर्णांक nbufs;		/* How many are alloc'd */
	पूर्णांक next_buf;			/* Next to consume (dev_lock) */

	अक्षर bus_info[32];		/* querycap bus_info */

	/* DMA buffers - vदो_स्मृति mode */
#अगर_घोषित MCAM_MODE_VMALLOC
	अचिन्हित पूर्णांक dma_buf_size;	/* allocated size */
	व्योम *dma_bufs[MAX_DMA_BUFS];	/* Internal buffer addresses */
	dma_addr_t dma_handles[MAX_DMA_BUFS]; /* Buffer bus addresses */
	काष्ठा tasklet_काष्ठा s_tasklet;
#पूर्ण_अगर
	अचिन्हित पूर्णांक sequence;		/* Frame sequence number */
	अचिन्हित पूर्णांक buf_seq[MAX_DMA_BUFS]; /* Sequence क्रम inभागidual bufs */

	/* DMA buffers - DMA modes */
	काष्ठा mcam_vb_buffer *vb_bufs[MAX_DMA_BUFS];

	/* Mode-specअगरic ops, set at खोलो समय */
	व्योम (*dma_setup)(काष्ठा mcam_camera *cam);
	व्योम (*frame_complete)(काष्ठा mcam_camera *cam, पूर्णांक frame);

	/* Current operating parameters */
	काष्ठा v4l2_pix_क्रमmat pix_क्रमmat;
	u32 mbus_code;

	/* Locks */
	काष्ठा mutex s_mutex; /* Access to this काष्ठाure */
पूर्ण;


/*
 * Register I/O functions.  These are here because the platक्रमm code
 * may legitimately need to mess with the रेजिस्टर space.
 */
/*
 * Device रेजिस्टर I/O
 */
अटल अंतरभूत व्योम mcam_reg_ग_लिखो(काष्ठा mcam_camera *cam, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक val)
अणु
	ioग_लिखो32(val, cam->regs + reg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mcam_reg_पढ़ो(काष्ठा mcam_camera *cam,
		अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32(cam->regs + reg);
पूर्ण


अटल अंतरभूत व्योम mcam_reg_ग_लिखो_mask(काष्ठा mcam_camera *cam, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक v = mcam_reg_पढ़ो(cam, reg);

	v = (v & ~mask) | (val & mask);
	mcam_reg_ग_लिखो(cam, reg, v);
पूर्ण

अटल अंतरभूत व्योम mcam_reg_clear_bit(काष्ठा mcam_camera *cam,
		अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	mcam_reg_ग_लिखो_mask(cam, reg, 0, val);
पूर्ण

अटल अंतरभूत व्योम mcam_reg_set_bit(काष्ठा mcam_camera *cam,
		अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	mcam_reg_ग_लिखो_mask(cam, reg, val, val);
पूर्ण

/*
 * Functions क्रम use by platक्रमm code.
 */
पूर्णांक mccic_रेजिस्टर(काष्ठा mcam_camera *cam);
पूर्णांक mccic_irq(काष्ठा mcam_camera *cam, अचिन्हित पूर्णांक irqs);
व्योम mccic_shutकरोwn(काष्ठा mcam_camera *cam);
व्योम mccic_suspend(काष्ठा mcam_camera *cam);
पूर्णांक mccic_resume(काष्ठा mcam_camera *cam);

/*
 * Register definitions क्रम the m88alp01 camera पूर्णांकerface.  Offsets in bytes
 * as given in the spec.
 */
#घोषणा REG_Y0BAR	0x00
#घोषणा REG_Y1BAR	0x04
#घोषणा REG_Y2BAR	0x08
#घोषणा REG_U0BAR	0x0c
#घोषणा REG_U1BAR	0x10
#घोषणा REG_U2BAR	0x14
#घोषणा REG_V0BAR	0x18
#घोषणा REG_V1BAR	0x1C
#घोषणा REG_V2BAR	0x20

/*
 * रेजिस्टर definitions क्रम MIPI support
 */
#घोषणा REG_CSI2_CTRL0	0x100
#घोषणा   CSI2_C0_MIPI_EN (0x1 << 0)
#घोषणा   CSI2_C0_ACT_LANE(n) ((n-1) << 1)
#घोषणा REG_CSI2_DPHY3	0x12c
#घोषणा REG_CSI2_DPHY5	0x134
#घोषणा REG_CSI2_DPHY6	0x138

/* ... */

#घोषणा REG_IMGPITCH	0x24	/* Image pitch रेजिस्टर */
#घोषणा   IMGP_YP_SHFT	  2		/* Y pitch params */
#घोषणा   IMGP_YP_MASK	  0x00003ffc	/* Y pitch field */
#घोषणा	  IMGP_UVP_SHFT	  18		/* UV pitch (planar) */
#घोषणा   IMGP_UVP_MASK   0x3ffc0000
#घोषणा REG_IRQSTATRAW	0x28	/* RAW IRQ Status */
#घोषणा   IRQ_खातापूर्ण0	  0x00000001	/* End of frame 0 */
#घोषणा   IRQ_खातापूर्ण1	  0x00000002	/* End of frame 1 */
#घोषणा   IRQ_खातापूर्ण2	  0x00000004	/* End of frame 2 */
#घोषणा   IRQ_SOF0	  0x00000008	/* Start of frame 0 */
#घोषणा   IRQ_SOF1	  0x00000010	/* Start of frame 1 */
#घोषणा   IRQ_SOF2	  0x00000020	/* Start of frame 2 */
#घोषणा   IRQ_OVERFLOW	  0x00000040	/* FIFO overflow */
#घोषणा   IRQ_TWSIW	  0x00010000	/* TWSI (smbus) ग_लिखो */
#घोषणा   IRQ_TWSIR	  0x00020000	/* TWSI पढ़ो */
#घोषणा   IRQ_TWSIE	  0x00040000	/* TWSI error */
#घोषणा   TWSIIRQS (IRQ_TWSIW|IRQ_TWSIR|IRQ_TWSIE)
#घोषणा   FRAMEIRQS (IRQ_खातापूर्ण0|IRQ_खातापूर्ण1|IRQ_खातापूर्ण2|IRQ_SOF0|IRQ_SOF1|IRQ_SOF2)
#घोषणा   ALLIRQS (TWSIIRQS|FRAMEIRQS|IRQ_OVERFLOW)
#घोषणा REG_IRQMASK	0x2c	/* IRQ mask - same bits as IRQSTAT */
#घोषणा REG_IRQSTAT	0x30	/* IRQ status / clear */

#घोषणा REG_IMGSIZE	0x34	/* Image size */
#घोषणा  IMGSZ_V_MASK	  0x1fff0000
#घोषणा  IMGSZ_V_SHIFT	  16
#घोषणा	 IMGSZ_H_MASK	  0x00003fff
#घोषणा REG_IMGOFFSET	0x38	/* IMage offset */

#घोषणा REG_CTRL0	0x3c	/* Control 0 */
#घोषणा   C0_ENABLE	  0x00000001	/* Makes the whole thing go */

/* Mask क्रम all the क्रमmat bits */
#घोषणा   C0_DF_MASK	  0x00fffffc    /* Bits 2-23 */

/* RGB ordering */
#घोषणा	  C0_RGB4_RGBX	  0x00000000
#घोषणा	  C0_RGB4_XRGB	  0x00000004
#घोषणा	  C0_RGB4_BGRX	  0x00000008
#घोषणा	  C0_RGB4_XBGR	  0x0000000c
#घोषणा	  C0_RGB5_RGGB	  0x00000000
#घोषणा	  C0_RGB5_GRBG	  0x00000004
#घोषणा	  C0_RGB5_GBRG	  0x00000008
#घोषणा	  C0_RGB5_BGGR	  0x0000000c

/* Spec has two fields क्रम DIN and DOUT, but they must match, so
   combine them here. */
#घोषणा	  C0_DF_YUV	  0x00000000	/* Data is YUV	    */
#घोषणा	  C0_DF_RGB	  0x000000a0	/* ... RGB		    */
#घोषणा	  C0_DF_BAYER	  0x00000140	/* ... Bayer		    */
/* 8-8-8 must be missing from the below - ask */
#घोषणा	  C0_RGBF_565	  0x00000000
#घोषणा	  C0_RGBF_444	  0x00000800
#घोषणा	  C0_RGB_BGR	  0x00001000	/* Blue comes first */
#घोषणा	  C0_YUV_PLANAR	  0x00000000	/* YUV 422 planar क्रमmat */
#घोषणा	  C0_YUV_PACKED	  0x00008000	/* YUV 422 packed	*/
#घोषणा	  C0_YUV_420PL	  0x0000a000	/* YUV 420 planar	*/
/* Think that 420 packed must be 111 - ask */
#घोषणा	  C0_YUVE_YUYV	  0x00000000	/* Y1CbY0Cr		*/
#घोषणा	  C0_YUVE_YVYU	  0x00010000	/* Y1CrY0Cb		*/
#घोषणा	  C0_YUVE_VYUY	  0x00020000	/* CrY1CbY0		*/
#घोषणा	  C0_YUVE_UYVY	  0x00030000	/* CbY1CrY0		*/
#घोषणा	  C0_YUVE_NOSWAP  0x00000000	/* no bytes swapping	*/
#घोषणा	  C0_YUVE_SWAP13  0x00010000	/* swap byte 1 and 3	*/
#घोषणा	  C0_YUVE_SWAP24  0x00020000	/* swap byte 2 and 4	*/
#घोषणा	  C0_YUVE_SWAP1324 0x00030000	/* swap bytes 1&3 and 2&4 */
/* Bayer bits 18,19 अगर needed */
#घोषणा	  C0_खातापूर्ण_VSYNC	  0x00400000	/* Generate खातापूर्ण by VSYNC */
#घोषणा	  C0_VEDGE_CTRL   0x00800000	/* Detect falling edge of VSYNC */
#घोषणा	  C0_HPOL_LOW	  0x01000000	/* HSYNC polarity active low */
#घोषणा	  C0_VPOL_LOW	  0x02000000	/* VSYNC polarity active low */
#घोषणा	  C0_VCLK_LOW	  0x04000000	/* VCLK on falling edge */
#घोषणा	  C0_DOWNSCALE	  0x08000000	/* Enable करोwnscaler */
/* SIFMODE */
#घोषणा	  C0_SIF_HVSYNC	  0x00000000	/* Use H/VSYNC */
#घोषणा	  C0_SOF_NOSYNC	  0x40000000	/* Use inband active संकेतing */
#घोषणा	  C0_SIFM_MASK	  0xc0000000	/* SIF mode bits */

/* Bits below C1_444ALPHA are not present in Cafe */
#घोषणा REG_CTRL1	0x40	/* Control 1 */
#घोषणा	  C1_CLKGATE	  0x00000001	/* Sensor घड़ी gate */
#घोषणा   C1_DESC_ENA	  0x00000100	/* DMA descriptor enable */
#घोषणा   C1_DESC_3WORD   0x00000200	/* Three-word descriptors used */
#घोषणा	  C1_444ALPHA	  0x00f00000	/* Alpha field in RGB444 */
#घोषणा	  C1_ALPHA_SHFT	  20
#घोषणा	  C1_DMAB32	  0x00000000	/* 32-byte DMA burst */
#घोषणा	  C1_DMAB16	  0x02000000	/* 16-byte DMA burst */
#घोषणा	  C1_DMAB64	  0x04000000	/* 64-byte DMA burst */
#घोषणा	  C1_DMAB_MASK	  0x06000000
#घोषणा	  C1_TWOBUFS	  0x08000000	/* Use only two DMA buffers */
#घोषणा	  C1_PWRDWN	  0x10000000	/* Power करोwn */

#घोषणा REG_CLKCTRL	0x88	/* Clock control */
#घोषणा	  CLK_DIV_MASK	  0x0000ffff	/* Upper bits RW "reserved" */

/* This appears to be a Cafe-only रेजिस्टर */
#घोषणा REG_UBAR	0xc4	/* Upper base address रेजिस्टर */

/* Armada 610 DMA descriptor रेजिस्टरs */
#घोषणा	REG_DMA_DESC_Y	0x200
#घोषणा	REG_DMA_DESC_U	0x204
#घोषणा	REG_DMA_DESC_V	0x208
#घोषणा REG_DESC_LEN_Y	0x20c	/* Lengths are in bytes */
#घोषणा	REG_DESC_LEN_U	0x210
#घोषणा REG_DESC_LEN_V	0x214

/*
 * Useful stuff that probably beदीर्घs somewhere global.
 */
#घोषणा VGA_WIDTH	640
#घोषणा VGA_HEIGHT	480

#पूर्ण_अगर /* _MCAM_CORE_H */
