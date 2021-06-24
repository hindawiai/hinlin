<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Motion Eye video4linux driver क्रम Sony Vaio PictureBook
 *
 * Copyright (C) 2001-2004 Stelian Pop <stelian@popies.net>
 *
 * Copyright (C) 2001-2002 Alcथखve <www.alcove.com>
 *
 * Copyright (C) 2000 Andrew Tridgell <tridge@valinux.com>
 *
 * Earlier work by Werner Almesberger, Paul `Rusty' Russell and Paul Mackerras.
 *
 * Some parts borrowed from various video4linux drivers, especially
 * bttv-driver.c and zoran.c, see original files क्रम credits.
 */

#अगर_अघोषित _MEYE_PRIV_H_
#घोषणा _MEYE_PRIV_H_

#घोषणा MEYE_DRIVER_MAJORVERSION	 1
#घोषणा MEYE_DRIVER_MINORVERSION	14

#घोषणा MEYE_DRIVER_VERSION __stringअगरy(MEYE_DRIVER_MAJORVERSION) "." \
			    __stringअगरy(MEYE_DRIVER_MINORVERSION)

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kfअगरo.h>
#समावेश <media/v4l2-ctrls.h>

/****************************************************************************/
/* Motion JPEG chip रेजिस्टरs                                               */
/****************************************************************************/

/* Motion JPEG chip PCI configuration रेजिस्टरs */
#घोषणा MCHIP_PCI_POWER_CSR		0x54
#घोषणा MCHIP_PCI_MCORE_STATUS		0x60		/* see HIC_STATUS   */
#घोषणा MCHIP_PCI_HOSTUSEREQ_SET	0x64
#घोषणा MCHIP_PCI_HOSTUSEREQ_CLR	0x68
#घोषणा MCHIP_PCI_LOWPOWER_SET		0x6c
#घोषणा MCHIP_PCI_LOWPOWER_CLR		0x70
#घोषणा MCHIP_PCI_SOFTRESET_SET		0x74

/* Motion JPEG chip memory mapped रेजिस्टरs */
#घोषणा MCHIP_MM_REGS			0x200		/* 512 bytes        */
#घोषणा MCHIP_REG_TIMEOUT		1000		/* reg access, ~us  */
#घोषणा MCHIP_MCC_VRJ_TIMEOUT		1000		/* MCC & VRJ access */

#घोषणा MCHIP_MM_PCI_MODE		0x00		/* PCI access mode */
#घोषणा MCHIP_MM_PCI_MODE_RETRY		0x00000001	/* retry mode */
#घोषणा MCHIP_MM_PCI_MODE_MASTER	0x00000002	/* master access */
#घोषणा MCHIP_MM_PCI_MODE_READ_LINE	0x00000004	/* पढ़ो line */

#घोषणा MCHIP_MM_INTA			0x04		/* Int status/mask */
#घोषणा MCHIP_MM_INTA_MCC		0x00000001	/* MCC पूर्णांकerrupt */
#घोषणा MCHIP_MM_INTA_VRJ		0x00000002	/* VRJ पूर्णांकerrupt */
#घोषणा MCHIP_MM_INTA_HIC_1		0x00000004	/* one frame करोne */
#घोषणा MCHIP_MM_INTA_HIC_1_MASK	0x00000400	/* 1: enable */
#घोषणा MCHIP_MM_INTA_HIC_END		0x00000008	/* all frames करोne */
#घोषणा MCHIP_MM_INTA_HIC_END_MASK	0x00000800
#घोषणा MCHIP_MM_INTA_JPEG		0x00000010	/* decompress. error */
#घोषणा MCHIP_MM_INTA_JPEG_MASK		0x00001000
#घोषणा MCHIP_MM_INTA_CAPTURE		0x00000020	/* capture end */
#घोषणा MCHIP_MM_INTA_PCI_ERR		0x00000040	/* PCI error */
#घोषणा MCHIP_MM_INTA_PCI_ERR_MASK	0x00004000

#घोषणा MCHIP_MM_PT_ADDR		0x08		/* page table address*/
							/* n*4kB */
#घोषणा MCHIP_NB_PAGES			1024		/* pages क्रम display */
#घोषणा MCHIP_NB_PAGES_MJPEG		256		/* pages क्रम mjpeg */

#घोषणा MCHIP_MM_FIR(n)			(0x0c+(n)*4)	/* Frame info 0-3 */
#घोषणा MCHIP_MM_FIR_RDY		0x00000001	/* frame पढ़ोy */
#घोषणा MCHIP_MM_FIR_FAILFR_MASK	0xf8000000	/* # of failed frames */
#घोषणा MCHIP_MM_FIR_FAILFR_SHIFT	27

	/* continuous comp/decomp mode */
#घोषणा MCHIP_MM_FIR_C_ENDL_MASK	0x000007fe	/* end DW [10] */
#घोषणा MCHIP_MM_FIR_C_ENDL_SHIFT	1
#घोषणा MCHIP_MM_FIR_C_ENDP_MASK	0x0007f800	/* end page [8] */
#घोषणा MCHIP_MM_FIR_C_ENDP_SHIFT	11
#घोषणा MCHIP_MM_FIR_C_STARTP_MASK	0x07f80000	/* start page [8] */
#घोषणा MCHIP_MM_FIR_C_STARTP_SHIFT	19

	/* continuous picture output mode */
#घोषणा MCHIP_MM_FIR_O_STARTP_MASK	0x7ffe0000	/* start page [10] */
#घोषणा MCHIP_MM_FIR_O_STARTP_SHIFT	17

#घोषणा MCHIP_MM_FIFO_DATA		0x1c		/* PCI TGT FIFO data */
#घोषणा MCHIP_MM_FIFO_STATUS		0x20		/* PCI TGT FIFO stat */
#घोषणा MCHIP_MM_FIFO_MASK		0x00000003
#घोषणा MCHIP_MM_FIFO_WAIT_OR_READY	0x00000002      /* Bits common to WAIT & READY*/
#घोषणा MCHIP_MM_FIFO_IDLE		0x0		/* HIC idle */
#घोषणा MCHIP_MM_FIFO_IDLE1		0x1		/* idem ??? */
#घोषणा	MCHIP_MM_FIFO_WAIT		0x2		/* रुको request */
#घोषणा MCHIP_MM_FIFO_READY		0x3		/* data पढ़ोy */

#घोषणा MCHIP_HIC_HOST_USEREQ		0x40		/* host uses MCORE */

#घोषणा MCHIP_HIC_TP_BUSY		0x44		/* taking picture */

#घोषणा MCHIP_HIC_PIC_SAVED		0x48		/* pic in SDRAM */

#घोषणा MCHIP_HIC_LOWPOWER		0x4c		/* घड़ी stopped */

#घोषणा MCHIP_HIC_CTL			0x50		/* HIC control */
#घोषणा MCHIP_HIC_CTL_SOFT_RESET	0x00000001	/* MCORE reset */
#घोषणा MCHIP_HIC_CTL_MCORE_RDY		0x00000002	/* MCORE पढ़ोy */

#घोषणा MCHIP_HIC_CMD			0x54		/* HIC command */
#घोषणा MCHIP_HIC_CMD_BITS		0x00000003      /* cmd width=[1:0]*/
#घोषणा MCHIP_HIC_CMD_NOOP		0x0
#घोषणा MCHIP_HIC_CMD_START		0x1
#घोषणा MCHIP_HIC_CMD_STOP		0x2

#घोषणा MCHIP_HIC_MODE			0x58
#घोषणा MCHIP_HIC_MODE_NOOP		0x0
#घोषणा MCHIP_HIC_MODE_STILL_CAP	0x1		/* still pic capt */
#घोषणा MCHIP_HIC_MODE_DISPLAY		0x2		/* display */
#घोषणा MCHIP_HIC_MODE_STILL_COMP	0x3		/* still pic comp. */
#घोषणा MCHIP_HIC_MODE_STILL_DECOMP	0x4		/* still pic decomp. */
#घोषणा MCHIP_HIC_MODE_CONT_COMP	0x5		/* cont capt+comp */
#घोषणा MCHIP_HIC_MODE_CONT_DECOMP	0x6		/* cont decomp+disp */
#घोषणा MCHIP_HIC_MODE_STILL_OUT	0x7		/* still pic output */
#घोषणा MCHIP_HIC_MODE_CONT_OUT		0x8		/* cont output */

#घोषणा MCHIP_HIC_STATUS		0x5c
#घोषणा MCHIP_HIC_STATUS_MCC_RDY	0x00000001	/* MCC reg acc ok */
#घोषणा MCHIP_HIC_STATUS_VRJ_RDY	0x00000002	/* VRJ reg acc ok */
#घोषणा MCHIP_HIC_STATUS_IDLE           0x00000003
#घोषणा MCHIP_HIC_STATUS_CAPDIS		0x00000004	/* cap/disp in prog */
#घोषणा MCHIP_HIC_STATUS_COMPDEC	0x00000008	/* (de)comp in prog */
#घोषणा MCHIP_HIC_STATUS_BUSY		0x00000010	/* HIC busy */

#घोषणा MCHIP_HIC_S_RATE		0x60		/* MJPEG # frames */

#घोषणा MCHIP_HIC_PCI_VFMT		0x64		/* video क्रमmat */
#घोषणा MCHIP_HIC_PCI_VFMT_YVYU		0x00000001	/* 0: V Y' U Y */
							/* 1: Y' V Y U */

#घोषणा MCHIP_MCC_CMD			0x80		/* MCC commands */
#घोषणा MCHIP_MCC_CMD_INITIAL		0x0		/* idle ? */
#घोषणा MCHIP_MCC_CMD_IIC_START_SET	0x1
#घोषणा MCHIP_MCC_CMD_IIC_END_SET	0x2
#घोषणा MCHIP_MCC_CMD_FM_WRITE		0x3		/* frame memory */
#घोषणा MCHIP_MCC_CMD_FM_READ		0x4
#घोषणा MCHIP_MCC_CMD_FM_STOP		0x5
#घोषणा MCHIP_MCC_CMD_CAPTURE		0x6
#घोषणा MCHIP_MCC_CMD_DISPLAY		0x7
#घोषणा MCHIP_MCC_CMD_END_DISP		0x8
#घोषणा MCHIP_MCC_CMD_STILL_COMP	0x9
#घोषणा MCHIP_MCC_CMD_STILL_DECOMP	0xa
#घोषणा MCHIP_MCC_CMD_STILL_OUTPUT	0xb
#घोषणा MCHIP_MCC_CMD_CONT_OUTPUT	0xc
#घोषणा MCHIP_MCC_CMD_CONT_COMP		0xd
#घोषणा MCHIP_MCC_CMD_CONT_DECOMP	0xe
#घोषणा MCHIP_MCC_CMD_RESET		0xf		/* MCC reset */

#घोषणा MCHIP_MCC_IIC_WR		0x84

#घोषणा MCHIP_MCC_MCC_WR		0x88

#घोषणा MCHIP_MCC_MCC_RD		0x8c

#घोषणा MCHIP_MCC_STATUS		0x90
#घोषणा MCHIP_MCC_STATUS_CAPT		0x00000001	/* capturing */
#घोषणा MCHIP_MCC_STATUS_DISP		0x00000002	/* displaying */
#घोषणा MCHIP_MCC_STATUS_COMP		0x00000004	/* compressing */
#घोषणा MCHIP_MCC_STATUS_DECOMP		0x00000008	/* decompressing */
#घोषणा MCHIP_MCC_STATUS_MCC_WR		0x00000010	/* रेजिस्टर पढ़ोy */
#घोषणा MCHIP_MCC_STATUS_MCC_RD		0x00000020	/* रेजिस्टर पढ़ोy */
#घोषणा MCHIP_MCC_STATUS_IIC_WR		0x00000040	/* रेजिस्टर पढ़ोy */
#घोषणा MCHIP_MCC_STATUS_OUTPUT		0x00000080	/* output in prog */

#घोषणा MCHIP_MCC_SIG_POLARITY		0x94
#घोषणा MCHIP_MCC_SIG_POL_VS_H		0x00000001	/* VS active-high */
#घोषणा MCHIP_MCC_SIG_POL_HS_H		0x00000002	/* HS active-high */
#घोषणा MCHIP_MCC_SIG_POL_DOE_H		0x00000004	/* DOE active-high */

#घोषणा MCHIP_MCC_IRQ			0x98
#घोषणा MCHIP_MCC_IRQ_CAPDIS_STRT	0x00000001	/* cap/disp started */
#घोषणा MCHIP_MCC_IRQ_CAPDIS_STRT_MASK	0x00000010
#घोषणा MCHIP_MCC_IRQ_CAPDIS_END	0x00000002	/* cap/disp ended */
#घोषणा MCHIP_MCC_IRQ_CAPDIS_END_MASK	0x00000020
#घोषणा MCHIP_MCC_IRQ_COMPDEC_STRT	0x00000004	/* (de)comp started */
#घोषणा MCHIP_MCC_IRQ_COMPDEC_STRT_MASK	0x00000040
#घोषणा MCHIP_MCC_IRQ_COMPDEC_END	0x00000008	/* (de)comp ended */
#घोषणा MCHIP_MCC_IRQ_COMPDEC_END_MASK	0x00000080

#घोषणा MCHIP_MCC_HSTART		0x9c		/* video in */
#घोषणा MCHIP_MCC_VSTART		0xa0
#घोषणा MCHIP_MCC_HCOUNT		0xa4
#घोषणा MCHIP_MCC_VCOUNT		0xa8
#घोषणा MCHIP_MCC_R_XBASE		0xac		/* capt/disp */
#घोषणा MCHIP_MCC_R_YBASE		0xb0
#घोषणा MCHIP_MCC_R_XRANGE		0xb4
#घोषणा MCHIP_MCC_R_YRANGE		0xb8
#घोषणा MCHIP_MCC_B_XBASE		0xbc		/* comp/decomp */
#घोषणा MCHIP_MCC_B_YBASE		0xc0
#घोषणा MCHIP_MCC_B_XRANGE		0xc4
#घोषणा MCHIP_MCC_B_YRANGE		0xc8

#घोषणा MCHIP_MCC_R_SAMPLING		0xcc		/* 1: 1:4 */

#घोषणा MCHIP_VRJ_CMD			0x100		/* VRJ commands */

/* VRJ रेजिस्टरs (see table 12.2.4) */
#घोषणा MCHIP_VRJ_COMPRESSED_DATA	0x1b0
#घोषणा MCHIP_VRJ_PIXEL_DATA		0x1b8

#घोषणा MCHIP_VRJ_BUS_MODE		0x100
#घोषणा MCHIP_VRJ_SIGNAL_ACTIVE_LEVEL	0x108
#घोषणा MCHIP_VRJ_PDAT_USE		0x110
#घोषणा MCHIP_VRJ_MODE_SPECIFY		0x118
#घोषणा MCHIP_VRJ_LIMIT_COMPRESSED_LO	0x120
#घोषणा MCHIP_VRJ_LIMIT_COMPRESSED_HI	0x124
#घोषणा MCHIP_VRJ_COMP_DATA_FORMAT	0x128
#घोषणा MCHIP_VRJ_TABLE_DATA		0x140
#घोषणा MCHIP_VRJ_RESTART_INTERVAL	0x148
#घोषणा MCHIP_VRJ_NUM_LINES		0x150
#घोषणा MCHIP_VRJ_NUM_PIXELS		0x158
#घोषणा MCHIP_VRJ_NUM_COMPONENTS	0x160
#घोषणा MCHIP_VRJ_SOF1			0x168
#घोषणा MCHIP_VRJ_SOF2			0x170
#घोषणा MCHIP_VRJ_SOF3			0x178
#घोषणा MCHIP_VRJ_SOF4			0x180
#घोषणा MCHIP_VRJ_SOS			0x188
#घोषणा MCHIP_VRJ_SOFT_RESET		0x190

#घोषणा MCHIP_VRJ_STATUS		0x1c0
#घोषणा MCHIP_VRJ_STATUS_BUSY		0x00001
#घोषणा MCHIP_VRJ_STATUS_COMP_ACCESS	0x00002
#घोषणा MCHIP_VRJ_STATUS_PIXEL_ACCESS	0x00004
#घोषणा MCHIP_VRJ_STATUS_ERROR		0x00008

#घोषणा MCHIP_VRJ_IRQ_FLAG		0x1c8
#घोषणा MCHIP_VRJ_ERROR_REPORT		0x1d8

#घोषणा MCHIP_VRJ_START_COMMAND		0x1a0

/****************************************************************************/
/* Driver definitions.                                                      */
/****************************************************************************/

/* Sony Programmable I/O Controller क्रम accessing the camera commands */
#समावेश <linux/sony-laptop.h>

/* निजी API definitions */
#समावेश <linux/meye.h>
#समावेश <linux/mutex.h>


/* Enable jpg software correction */
#घोषणा MEYE_JPEG_CORRECTION	1

/* Maximum size of a buffer */
#घोषणा MEYE_MAX_बफ_मानE	614400	/* 640 * 480 * 2 */

/* Maximum number of buffers */
#घोषणा MEYE_MAX_BUFNBRS	32

/* State of a buffer */
#घोषणा MEYE_BUF_UNUSED	0	/* not used */
#घोषणा MEYE_BUF_USING	1	/* currently grabbing / playing */
#घोषणा MEYE_BUF_DONE	2	/* करोne */

/* grab buffer */
काष्ठा meye_grab_buffer अणु
	पूर्णांक state;			/* state of buffer */
	अचिन्हित दीर्घ size;		/* size of jpg frame */
	u64 ts;				/* बारtamp */
	अचिन्हित दीर्घ sequence;		/* sequence number */
पूर्ण;

/* size of kfअगरos containing buffer indices */
#घोषणा MEYE_QUEUE_SIZE	MEYE_MAX_BUFNBRS

/* Motion Eye device काष्ठाure */
काष्ठा meye अणु
	काष्ठा v4l2_device v4l2_dev;	/* Main v4l2_device काष्ठा */
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा pci_dev *mchip_dev;	/* pci device */
	u8 mchip_irq;			/* irq */
	u8 mchip_mode;			/* actual mchip mode: HIC_MODE... */
	u8 mchip_fnum;			/* current mchip frame number */
	अचिन्हित अक्षर __iomem *mchip_mmregs;/* mchip: memory mapped रेजिस्टरs */
	u8 *mchip_ptable[MCHIP_NB_PAGES];/* mchip: ptable */
	व्योम *mchip_ptable_toc;		/* mchip: ptable toc */
	dma_addr_t mchip_dmahandle;	/* mchip: dma handle to ptable toc */
	अचिन्हित अक्षर *grab_fbuffer;	/* capture framebuffer */
	अचिन्हित अक्षर *grab_temp;	/* temporary buffer */
					/* list of buffers */
	काष्ठा meye_grab_buffer grab_buffer[MEYE_MAX_BUFNBRS];
	पूर्णांक vma_use_count[MEYE_MAX_BUFNBRS]; /* mmap count */
	काष्ठा mutex lock;		/* mutex क्रम खोलो/mmap... */
	काष्ठा kfअगरo grabq;		/* queue क्रम buffers to be grabbed */
	spinlock_t grabq_lock;		/* lock protecting the queue */
	काष्ठा kfअगरo करोneq;		/* queue क्रम grabbed buffers */
	spinlock_t करोneq_lock;		/* lock protecting the queue */
	रुको_queue_head_t proc_list;	/* रुको queue */
	काष्ठा video_device vdev;	/* video device parameters */
	u16 brightness;
	u16 hue;
	u16 contrast;
	u16 colour;
	काष्ठा meye_params params;	/* additional parameters */
	अचिन्हित दीर्घ in_use;		/* set to 1 अगर the device is in use */
	u8 pm_mchip_mode;		/* old mchip mode */
पूर्ण;

#पूर्ण_अगर
