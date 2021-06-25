<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***************************************************************************
 *   Copyright (C) 2006-2010 by Marin Mitov                                *
 *   mitov@issp.bas.bg                                                     *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

/*    DT3155 header file    */
#अगर_अघोषित _DT3155_H_
#घोषणा _DT3155_H_

#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/videobuf2-v4l2.h>

#घोषणा DT3155_NAME "dt3155"
#घोषणा DT3155_VER_MAJ 2
#घोषणा DT3155_VER_MIN 0
#घोषणा DT3155_VER_EXT 0
#घोषणा DT3155_VERSION  __stringअगरy(DT3155_VER_MAJ)	"."		\
			__stringअगरy(DT3155_VER_MIN)	"."		\
			__stringअगरy(DT3155_VER_EXT)

/* DT3155 Base Register offsets (memory mapped) */
#घोषणा EVEN_DMA_START	 0x00
#घोषणा ODD_DMA_START	 0x0C
#घोषणा EVEN_DMA_STRIDE  0x18
#घोषणा ODD_DMA_STRIDE	 0x24
#घोषणा EVEN_PIXEL_FMT	 0x30
#घोषणा ODD_PIXEL_FMT	 0x34
#घोषणा FIFO_TRIGGER	 0x38
#घोषणा XFER_MODE	 0x3C
#घोषणा CSR1		 0x40
#घोषणा RETRY_WAIT_CNT	 0x44
#घोषणा INT_CSR		 0x48
#घोषणा EVEN_FLD_MASK	 0x4C
#घोषणा ODD_FLD_MASK	 0x50
#घोषणा MASK_LENGTH	 0x54
#घोषणा FIFO_FLAG_CNT	 0x58
#घोषणा IIC_CLK_DUR	 0x5C
#घोषणा IIC_CSR1	 0x60
#घोषणा IIC_CSR2	 0x64

/*  DT3155 Internal Registers indexes (i2c/IIC mapped) */
#घोषणा CSR2	     0x10
#घोषणा EVEN_CSR     0x11
#घोषणा ODD_CSR      0x12
#घोषणा CONFIG	     0x13
#घोषणा DT_ID	     0x1F
#घोषणा X_CLIP_START 0x20
#घोषणा Y_CLIP_START 0x22
#घोषणा X_CLIP_END   0x24
#घोषणा Y_CLIP_END   0x26
#घोषणा AD_ADDR      0x30
#घोषणा AD_LUT	     0x31
#घोषणा AD_CMD	     0x32
#घोषणा DIG_OUT      0x40
#घोषणा PM_LUT_ADDR  0x50
#घोषणा PM_LUT_DATA  0x51

/* AD command रेजिस्टर values  */
#घोषणा AD_CMD_REG   0x00
#घोषणा AD_POS_REF   0x01
#घोषणा AD_NEG_REF   0x02

/* CSR1 bit masks */
#घोषणा RANGE_EN       0x00008000
#घोषणा CRPT_DIS       0x00004000
#घोषणा ADDR_ERR_ODD   0x00000800
#घोषणा ADDR_ERR_EVEN  0x00000400
#घोषणा FLD_CRPT_ODD   0x00000200
#घोषणा FLD_CRPT_EVEN  0x00000100
#घोषणा FIFO_EN        0x00000080
#घोषणा SRST	       0x00000040
#घोषणा FLD_DN_ODD     0x00000020
#घोषणा FLD_DN_EVEN    0x00000010
/*   These should not be used.
 *   Use CAP_CONT_ODD/EVEN instead
#घोषणा CAP_SNGL_ODD   0x00000008
#घोषणा CAP_SNGL_EVEN  0x00000004
*/
#घोषणा CAP_CONT_ODD   0x00000002
#घोषणा CAP_CONT_EVEN  0x00000001

/*  INT_CSR bit masks */
#घोषणा FLD_START_EN	 0x00000400
#घोषणा FLD_END_ODD_EN	 0x00000200
#घोषणा FLD_END_EVEN_EN  0x00000100
#घोषणा FLD_START	 0x00000004
#घोषणा FLD_END_ODD	 0x00000002
#घोषणा FLD_END_EVEN	 0x00000001

/* IIC_CSR1 bit masks */
#घोषणा सूचीECT_ABORT	 0x00000200

/* IIC_CSR2 bit masks */
#घोषणा NEW_CYCLE   0x01000000
#घोषणा सूची_RD	    0x00010000
#घोषणा IIC_READ    0x01010000
#घोषणा IIC_WRITE   0x01000000

/* CSR2 bit masks */
#घोषणा DISP_PASS     0x40
#घोषणा BUSY_ODD      0x20
#घोषणा BUSY_EVEN     0x10
#घोषणा SYNC_PRESENT  0x08
#घोषणा VT_50HZ       0x04
#घोषणा SYNC_SNTL     0x02
#घोषणा CHROM_FILT    0x01
#घोषणा VT_60HZ       0x00

/* CSR_EVEN/ODD bit masks */
#घोषणा CSR_ERROR	0x04
#घोषणा CSR_SNGL	0x02
#घोषणा CSR_DONE	0x01

/* CONFIG bit masks */
#घोषणा PM_LUT_PGM     0x80
#घोषणा PM_LUT_SEL     0x40
#घोषणा CLIP_EN        0x20
#घोषणा HSCALE_EN      0x10
#घोषणा EXT_TRIG_UP    0x0C
#घोषणा EXT_TRIG_DOWN  0x04
#घोषणा ACQ_MODE_NEXT  0x02
#घोषणा ACQ_MODE_ODD   0x01
#घोषणा ACQ_MODE_EVEN  0x00

/* AD_CMD bit masks */
#घोषणा VIDEO_CNL_1  0x00
#घोषणा VIDEO_CNL_2  0x40
#घोषणा VIDEO_CNL_3  0x80
#घोषणा VIDEO_CNL_4  0xC0
#घोषणा SYNC_CNL_1   0x00
#घोषणा SYNC_CNL_2   0x10
#घोषणा SYNC_CNL_3   0x20
#घोषणा SYNC_CNL_4   0x30
#घोषणा SYNC_LVL_1   0x00
#घोषणा SYNC_LVL_2   0x04
#घोषणा SYNC_LVL_3   0x08
#घोषणा SYNC_LVL_4   0x0C

/* DT3155 identअगरicator */
#घोषणा DT3155_ID   0x20

/*    per board निजी data काष्ठाure   */
/**
 * काष्ठा dt3155_priv - निजी data काष्ठाure
 *
 * @v4l2_dev:		v4l2_device काष्ठाure
 * @vdev:		video_device काष्ठाure
 * @pdev:		poपूर्णांकer to pci_dev काष्ठाure
 * @vidq:		vb2_queue काष्ठाure
 * @curr_buf:		poपूर्णांकer to curren buffer
 * @mux:		mutex to protect the instance
 * @dmaq:		queue क्रम dma buffers
 * @lock:		spinlock क्रम dma queue
 * @std:		input standard
 * @width:		frame width
 * @height:		frame height
 * @input:		current input
 * @sequence:		frame counter
 * @stats:		statistics काष्ठाure
 * @regs:		local copy of mmio base रेजिस्टर
 * @csr2:		local copy of csr2 रेजिस्टर
 * @config:		local copy of config रेजिस्टर
 */
काष्ठा dt3155_priv अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device vdev;
	काष्ठा pci_dev *pdev;
	काष्ठा vb2_queue vidq;
	काष्ठा vb2_v4l2_buffer *curr_buf;
	काष्ठा mutex mux;
	काष्ठा list_head dmaq;
	spinlock_t lock;
	v4l2_std_id std;
	अचिन्हित width, height;
	अचिन्हित input;
	अचिन्हित पूर्णांक sequence;
	व्योम __iomem *regs;
	u8 csr2, config;
पूर्ण;

#पूर्ण_अगर /*  _DT3155_H_  */
