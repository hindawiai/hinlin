<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm_adsp.c  --  Wolfson ADSP support
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/list.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm_adsp.h"

#घोषणा adsp_crit(_dsp, fmt, ...) \
	dev_crit(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_ARGS__)
#घोषणा adsp_err(_dsp, fmt, ...) \
	dev_err(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_ARGS__)
#घोषणा adsp_warn(_dsp, fmt, ...) \
	dev_warn(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_ARGS__)
#घोषणा adsp_info(_dsp, fmt, ...) \
	dev_info(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_ARGS__)
#घोषणा adsp_dbg(_dsp, fmt, ...) \
	dev_dbg(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_ARGS__)

#घोषणा compr_err(_obj, fmt, ...) \
	adsp_err(_obj->dsp, "%s: " fmt, _obj->name ? _obj->name : "legacy", \
		 ##__VA_ARGS__)
#घोषणा compr_dbg(_obj, fmt, ...) \
	adsp_dbg(_obj->dsp, "%s: " fmt, _obj->name ? _obj->name : "legacy", \
		 ##__VA_ARGS__)

#घोषणा ADSP1_CONTROL_1                   0x00
#घोषणा ADSP1_CONTROL_2                   0x02
#घोषणा ADSP1_CONTROL_3                   0x03
#घोषणा ADSP1_CONTROL_4                   0x04
#घोषणा ADSP1_CONTROL_5                   0x06
#घोषणा ADSP1_CONTROL_6                   0x07
#घोषणा ADSP1_CONTROL_7                   0x08
#घोषणा ADSP1_CONTROL_8                   0x09
#घोषणा ADSP1_CONTROL_9                   0x0A
#घोषणा ADSP1_CONTROL_10                  0x0B
#घोषणा ADSP1_CONTROL_11                  0x0C
#घोषणा ADSP1_CONTROL_12                  0x0D
#घोषणा ADSP1_CONTROL_13                  0x0F
#घोषणा ADSP1_CONTROL_14                  0x10
#घोषणा ADSP1_CONTROL_15                  0x11
#घोषणा ADSP1_CONTROL_16                  0x12
#घोषणा ADSP1_CONTROL_17                  0x13
#घोषणा ADSP1_CONTROL_18                  0x14
#घोषणा ADSP1_CONTROL_19                  0x16
#घोषणा ADSP1_CONTROL_20                  0x17
#घोषणा ADSP1_CONTROL_21                  0x18
#घोषणा ADSP1_CONTROL_22                  0x1A
#घोषणा ADSP1_CONTROL_23                  0x1B
#घोषणा ADSP1_CONTROL_24                  0x1C
#घोषणा ADSP1_CONTROL_25                  0x1E
#घोषणा ADSP1_CONTROL_26                  0x20
#घोषणा ADSP1_CONTROL_27                  0x21
#घोषणा ADSP1_CONTROL_28                  0x22
#घोषणा ADSP1_CONTROL_29                  0x23
#घोषणा ADSP1_CONTROL_30                  0x24
#घोषणा ADSP1_CONTROL_31                  0x26

/*
 * ADSP1 Control 19
 */
#घोषणा ADSP1_WDMA_BUFFER_LENGTH_MASK     0x00FF  /* DSP1_WDMA_BUFFER_LENGTH - [7:0] */
#घोषणा ADSP1_WDMA_BUFFER_LENGTH_SHIFT         0  /* DSP1_WDMA_BUFFER_LENGTH - [7:0] */
#घोषणा ADSP1_WDMA_BUFFER_LENGTH_WIDTH         8  /* DSP1_WDMA_BUFFER_LENGTH - [7:0] */


/*
 * ADSP1 Control 30
 */
#घोषणा ADSP1_DBG_CLK_ENA                 0x0008  /* DSP1_DBG_CLK_ENA */
#घोषणा ADSP1_DBG_CLK_ENA_MASK            0x0008  /* DSP1_DBG_CLK_ENA */
#घोषणा ADSP1_DBG_CLK_ENA_SHIFT                3  /* DSP1_DBG_CLK_ENA */
#घोषणा ADSP1_DBG_CLK_ENA_WIDTH                1  /* DSP1_DBG_CLK_ENA */
#घोषणा ADSP1_SYS_ENA                     0x0004  /* DSP1_SYS_ENA */
#घोषणा ADSP1_SYS_ENA_MASK                0x0004  /* DSP1_SYS_ENA */
#घोषणा ADSP1_SYS_ENA_SHIFT                    2  /* DSP1_SYS_ENA */
#घोषणा ADSP1_SYS_ENA_WIDTH                    1  /* DSP1_SYS_ENA */
#घोषणा ADSP1_CORE_ENA                    0x0002  /* DSP1_CORE_ENA */
#घोषणा ADSP1_CORE_ENA_MASK               0x0002  /* DSP1_CORE_ENA */
#घोषणा ADSP1_CORE_ENA_SHIFT                   1  /* DSP1_CORE_ENA */
#घोषणा ADSP1_CORE_ENA_WIDTH                   1  /* DSP1_CORE_ENA */
#घोषणा ADSP1_START                       0x0001  /* DSP1_START */
#घोषणा ADSP1_START_MASK                  0x0001  /* DSP1_START */
#घोषणा ADSP1_START_SHIFT                      0  /* DSP1_START */
#घोषणा ADSP1_START_WIDTH                      1  /* DSP1_START */

/*
 * ADSP1 Control 31
 */
#घोषणा ADSP1_CLK_SEL_MASK                0x0007  /* CLK_SEL_ENA */
#घोषणा ADSP1_CLK_SEL_SHIFT                    0  /* CLK_SEL_ENA */
#घोषणा ADSP1_CLK_SEL_WIDTH                    3  /* CLK_SEL_ENA */

#घोषणा ADSP2_CONTROL                     0x0
#घोषणा ADSP2_CLOCKING                    0x1
#घोषणा ADSP2V2_CLOCKING                  0x2
#घोषणा ADSP2_STATUS1                     0x4
#घोषणा ADSP2_WDMA_CONFIG_1               0x30
#घोषणा ADSP2_WDMA_CONFIG_2               0x31
#घोषणा ADSP2V2_WDMA_CONFIG_2             0x32
#घोषणा ADSP2_RDMA_CONFIG_1               0x34

#घोषणा ADSP2_SCRATCH0                    0x40
#घोषणा ADSP2_SCRATCH1                    0x41
#घोषणा ADSP2_SCRATCH2                    0x42
#घोषणा ADSP2_SCRATCH3                    0x43

#घोषणा ADSP2V2_SCRATCH0_1                0x40
#घोषणा ADSP2V2_SCRATCH2_3                0x42

/*
 * ADSP2 Control
 */

#घोषणा ADSP2_MEM_ENA                     0x0010  /* DSP1_MEM_ENA */
#घोषणा ADSP2_MEM_ENA_MASK                0x0010  /* DSP1_MEM_ENA */
#घोषणा ADSP2_MEM_ENA_SHIFT                    4  /* DSP1_MEM_ENA */
#घोषणा ADSP2_MEM_ENA_WIDTH                    1  /* DSP1_MEM_ENA */
#घोषणा ADSP2_SYS_ENA                     0x0004  /* DSP1_SYS_ENA */
#घोषणा ADSP2_SYS_ENA_MASK                0x0004  /* DSP1_SYS_ENA */
#घोषणा ADSP2_SYS_ENA_SHIFT                    2  /* DSP1_SYS_ENA */
#घोषणा ADSP2_SYS_ENA_WIDTH                    1  /* DSP1_SYS_ENA */
#घोषणा ADSP2_CORE_ENA                    0x0002  /* DSP1_CORE_ENA */
#घोषणा ADSP2_CORE_ENA_MASK               0x0002  /* DSP1_CORE_ENA */
#घोषणा ADSP2_CORE_ENA_SHIFT                   1  /* DSP1_CORE_ENA */
#घोषणा ADSP2_CORE_ENA_WIDTH                   1  /* DSP1_CORE_ENA */
#घोषणा ADSP2_START                       0x0001  /* DSP1_START */
#घोषणा ADSP2_START_MASK                  0x0001  /* DSP1_START */
#घोषणा ADSP2_START_SHIFT                      0  /* DSP1_START */
#घोषणा ADSP2_START_WIDTH                      1  /* DSP1_START */

/*
 * ADSP2 घड़ीing
 */
#घोषणा ADSP2_CLK_SEL_MASK                0x0007  /* CLK_SEL_ENA */
#घोषणा ADSP2_CLK_SEL_SHIFT                    0  /* CLK_SEL_ENA */
#घोषणा ADSP2_CLK_SEL_WIDTH                    3  /* CLK_SEL_ENA */

/*
 * ADSP2V2 घड़ीing
 */
#घोषणा ADSP2V2_CLK_SEL_MASK             0x70000  /* CLK_SEL_ENA */
#घोषणा ADSP2V2_CLK_SEL_SHIFT                 16  /* CLK_SEL_ENA */
#घोषणा ADSP2V2_CLK_SEL_WIDTH                  3  /* CLK_SEL_ENA */

#घोषणा ADSP2V2_RATE_MASK                 0x7800  /* DSP_RATE */
#घोषणा ADSP2V2_RATE_SHIFT                    11  /* DSP_RATE */
#घोषणा ADSP2V2_RATE_WIDTH                     4  /* DSP_RATE */

/*
 * ADSP2 Status 1
 */
#घोषणा ADSP2_RAM_RDY                     0x0001
#घोषणा ADSP2_RAM_RDY_MASK                0x0001
#घोषणा ADSP2_RAM_RDY_SHIFT                    0
#घोषणा ADSP2_RAM_RDY_WIDTH                    1

/*
 * ADSP2 Lock support
 */
#घोषणा ADSP2_LOCK_CODE_0                    0x5555
#घोषणा ADSP2_LOCK_CODE_1                    0xAAAA

#घोषणा ADSP2_WATCHDOG                       0x0A
#घोषणा ADSP2_BUS_ERR_ADDR                   0x52
#घोषणा ADSP2_REGION_LOCK_STATUS             0x64
#घोषणा ADSP2_LOCK_REGION_1_LOCK_REGION_0    0x66
#घोषणा ADSP2_LOCK_REGION_3_LOCK_REGION_2    0x68
#घोषणा ADSP2_LOCK_REGION_5_LOCK_REGION_4    0x6A
#घोषणा ADSP2_LOCK_REGION_7_LOCK_REGION_6    0x6C
#घोषणा ADSP2_LOCK_REGION_9_LOCK_REGION_8    0x6E
#घोषणा ADSP2_LOCK_REGION_CTRL               0x7A
#घोषणा ADSP2_PMEM_ERR_ADDR_XMEM_ERR_ADDR    0x7C

#घोषणा ADSP2_REGION_LOCK_ERR_MASK           0x8000
#घोषणा ADSP2_ADDR_ERR_MASK                  0x4000
#घोषणा ADSP2_WDT_TIMEOUT_STS_MASK           0x2000
#घोषणा ADSP2_CTRL_ERR_PAUSE_ENA             0x0002
#घोषणा ADSP2_CTRL_ERR_EINT                  0x0001

#घोषणा ADSP2_BUS_ERR_ADDR_MASK              0x00FFFFFF
#घोषणा ADSP2_XMEM_ERR_ADDR_MASK             0x0000FFFF
#घोषणा ADSP2_PMEM_ERR_ADDR_MASK             0x7FFF0000
#घोषणा ADSP2_PMEM_ERR_ADDR_SHIFT            16
#घोषणा ADSP2_WDT_ENA_MASK                   0xFFFFFFFD

#घोषणा ADSP2_LOCK_REGION_SHIFT              16

#घोषणा ADSP_MAX_STD_CTRL_SIZE               512

#घोषणा WM_ADSP_ACKED_CTL_TIMEOUT_MS         100
#घोषणा WM_ADSP_ACKED_CTL_N_QUICKPOLLS       10
#घोषणा WM_ADSP_ACKED_CTL_MIN_VALUE          0
#घोषणा WM_ADSP_ACKED_CTL_MAX_VALUE          0xFFFFFF

/*
 * Event control messages
 */
#घोषणा WM_ADSP_FW_EVENT_SHUTDOWN            0x000001

/*
 * HALO प्रणाली info
 */
#घोषणा HALO_AHBM_WINDOW_DEBUG_0             0x02040
#घोषणा HALO_AHBM_WINDOW_DEBUG_1             0x02044

/*
 * HALO core
 */
#घोषणा HALO_SCRATCH1                        0x005c0
#घोषणा HALO_SCRATCH2                        0x005c8
#घोषणा HALO_SCRATCH3                        0x005d0
#घोषणा HALO_SCRATCH4                        0x005d8
#घोषणा HALO_CCM_CORE_CONTROL                0x41000
#घोषणा HALO_CORE_SOFT_RESET                 0x00010
#घोषणा HALO_WDT_CONTROL                     0x47000

/*
 * HALO MPU banks
 */
#घोषणा HALO_MPU_XMEM_ACCESS_0               0x43000
#घोषणा HALO_MPU_YMEM_ACCESS_0               0x43004
#घोषणा HALO_MPU_WINDOW_ACCESS_0             0x43008
#घोषणा HALO_MPU_XREG_ACCESS_0               0x4300C
#घोषणा HALO_MPU_YREG_ACCESS_0               0x43014
#घोषणा HALO_MPU_XMEM_ACCESS_1               0x43018
#घोषणा HALO_MPU_YMEM_ACCESS_1               0x4301C
#घोषणा HALO_MPU_WINDOW_ACCESS_1             0x43020
#घोषणा HALO_MPU_XREG_ACCESS_1               0x43024
#घोषणा HALO_MPU_YREG_ACCESS_1               0x4302C
#घोषणा HALO_MPU_XMEM_ACCESS_2               0x43030
#घोषणा HALO_MPU_YMEM_ACCESS_2               0x43034
#घोषणा HALO_MPU_WINDOW_ACCESS_2             0x43038
#घोषणा HALO_MPU_XREG_ACCESS_2               0x4303C
#घोषणा HALO_MPU_YREG_ACCESS_2               0x43044
#घोषणा HALO_MPU_XMEM_ACCESS_3               0x43048
#घोषणा HALO_MPU_YMEM_ACCESS_3               0x4304C
#घोषणा HALO_MPU_WINDOW_ACCESS_3             0x43050
#घोषणा HALO_MPU_XREG_ACCESS_3               0x43054
#घोषणा HALO_MPU_YREG_ACCESS_3               0x4305C
#घोषणा HALO_MPU_XM_VIO_ADDR                 0x43100
#घोषणा HALO_MPU_XM_VIO_STATUS               0x43104
#घोषणा HALO_MPU_YM_VIO_ADDR                 0x43108
#घोषणा HALO_MPU_YM_VIO_STATUS               0x4310C
#घोषणा HALO_MPU_PM_VIO_ADDR                 0x43110
#घोषणा HALO_MPU_PM_VIO_STATUS               0x43114
#घोषणा HALO_MPU_LOCK_CONFIG                 0x43140

/*
 * HALO_AHBM_WINDOW_DEBUG_1
 */
#घोषणा HALO_AHBM_CORE_ERR_ADDR_MASK         0x0fffff00
#घोषणा HALO_AHBM_CORE_ERR_ADDR_SHIFT                 8
#घोषणा HALO_AHBM_FLAGS_ERR_MASK             0x000000ff

/*
 * HALO_CCM_CORE_CONTROL
 */
#घोषणा HALO_CORE_EN                        0x00000001

/*
 * HALO_CORE_SOFT_RESET
 */
#घोषणा HALO_CORE_SOFT_RESET_MASK           0x00000001

/*
 * HALO_WDT_CONTROL
 */
#घोषणा HALO_WDT_EN_MASK                    0x00000001

/*
 * HALO_MPU_?M_VIO_STATUS
 */
#घोषणा HALO_MPU_VIO_STS_MASK               0x007e0000
#घोषणा HALO_MPU_VIO_STS_SHIFT                      17
#घोषणा HALO_MPU_VIO_ERR_WR_MASK            0x00008000
#घोषणा HALO_MPU_VIO_ERR_SRC_MASK           0x00007fff
#घोषणा HALO_MPU_VIO_ERR_SRC_SHIFT                   0

अटल काष्ठा wm_adsp_ops wm_adsp1_ops;
अटल काष्ठा wm_adsp_ops wm_adsp2_ops[];
अटल काष्ठा wm_adsp_ops wm_halo_ops;

काष्ठा wm_adsp_buf अणु
	काष्ठा list_head list;
	व्योम *buf;
पूर्ण;

अटल काष्ठा wm_adsp_buf *wm_adsp_buf_alloc(स्थिर व्योम *src, माप_प्रकार len,
					     काष्ठा list_head *list)
अणु
	काष्ठा wm_adsp_buf *buf = kzalloc(माप(*buf), GFP_KERNEL);

	अगर (buf == शून्य)
		वापस शून्य;

	buf->buf = vदो_स्मृति(len);
	अगर (!buf->buf) अणु
		kमुक्त(buf);
		वापस शून्य;
	पूर्ण
	स_नकल(buf->buf, src, len);

	अगर (list)
		list_add_tail(&buf->list, list);

	वापस buf;
पूर्ण

अटल व्योम wm_adsp_buf_मुक्त(काष्ठा list_head *list)
अणु
	जबतक (!list_empty(list)) अणु
		काष्ठा wm_adsp_buf *buf = list_first_entry(list,
							   काष्ठा wm_adsp_buf,
							   list);
		list_del(&buf->list);
		vमुक्त(buf->buf);
		kमुक्त(buf);
	पूर्ण
पूर्ण

#घोषणा WM_ADSP_FW_MBC_VSS  0
#घोषणा WM_ADSP_FW_HIFI     1
#घोषणा WM_ADSP_FW_TX       2
#घोषणा WM_ADSP_FW_TX_SPK   3
#घोषणा WM_ADSP_FW_RX       4
#घोषणा WM_ADSP_FW_RX_ANC   5
#घोषणा WM_ADSP_FW_CTRL     6
#घोषणा WM_ADSP_FW_ASR      7
#घोषणा WM_ADSP_FW_TRACE    8
#घोषणा WM_ADSP_FW_SPK_PROT 9
#घोषणा WM_ADSP_FW_SPK_CALI 10
#घोषणा WM_ADSP_FW_SPK_DIAG 11
#घोषणा WM_ADSP_FW_MISC     12

#घोषणा WM_ADSP_NUM_FW      13

अटल स्थिर अक्षर *wm_adsp_fw_text[WM_ADSP_NUM_FW] = अणु
	[WM_ADSP_FW_MBC_VSS] =  "MBC/VSS",
	[WM_ADSP_FW_HIFI] =     "MasterHiFi",
	[WM_ADSP_FW_TX] =       "Tx",
	[WM_ADSP_FW_TX_SPK] =   "Tx Speaker",
	[WM_ADSP_FW_RX] =       "Rx",
	[WM_ADSP_FW_RX_ANC] =   "Rx ANC",
	[WM_ADSP_FW_CTRL] =     "Voice Ctrl",
	[WM_ADSP_FW_ASR] =      "ASR Assist",
	[WM_ADSP_FW_TRACE] =    "Dbg Trace",
	[WM_ADSP_FW_SPK_PROT] = "Protection",
	[WM_ADSP_FW_SPK_CALI] = "Calibration",
	[WM_ADSP_FW_SPK_DIAG] = "Diagnostic",
	[WM_ADSP_FW_MISC] =     "Misc",
पूर्ण;

काष्ठा wm_adsp_प्रणाली_config_xm_hdr अणु
	__be32 sys_enable;
	__be32 fw_id;
	__be32 fw_rev;
	__be32 boot_status;
	__be32 watchकरोg;
	__be32 dma_buffer_size;
	__be32 rdma[6];
	__be32 wdma[8];
	__be32 build_job_name[3];
	__be32 build_job_number;
पूर्ण;

काष्ठा wm_halo_प्रणाली_config_xm_hdr अणु
	__be32 halo_heartbeat;
	__be32 build_job_name[3];
	__be32 build_job_number;
पूर्ण;

काष्ठा wm_adsp_alg_xm_काष्ठा अणु
	__be32 magic;
	__be32 smoothing;
	__be32 threshold;
	__be32 host_buf_ptr;
	__be32 start_seq;
	__be32 high_water_mark;
	__be32 low_water_mark;
	__be64 smoothed_घातer;
पूर्ण;

काष्ठा wm_adsp_host_buf_coeff_v1 अणु
	__be32 host_buf_ptr;		/* Host buffer poपूर्णांकer */
	__be32 versions;		/* Version numbers */
	__be32 name[4];			/* The buffer name */
पूर्ण;

काष्ठा wm_adsp_buffer अणु
	__be32 buf1_base;		/* Base addr of first buffer area */
	__be32 buf1_size;		/* Size of buf1 area in DSP words */
	__be32 buf2_base;		/* Base addr of 2nd buffer area */
	__be32 buf1_buf2_size;		/* Size of buf1+buf2 in DSP words */
	__be32 buf3_base;		/* Base addr of buf3 area */
	__be32 buf_total_size;		/* Size of buf1+buf2+buf3 in DSP words */
	__be32 high_water_mark;		/* Poपूर्णांक at which IRQ is निश्चितed */
	__be32 irq_count;		/* bits 1-31 count IRQ निश्चितions */
	__be32 irq_ack;			/* acked IRQ count, bit 0 enables IRQ */
	__be32 next_ग_लिखो_index;	/* word index of next ग_लिखो */
	__be32 next_पढ़ो_index;		/* word index of next पढ़ो */
	__be32 error;			/* error अगर any */
	__be32 oldest_block_index;	/* word index of oldest surviving */
	__be32 requested_शुरुआत;	/* how many blocks शुरुआत was करोne */
	__be32 reserved_space;		/* पूर्णांकernal */
	__be32 min_मुक्त;		/* min मुक्त space since stream start */
	__be32 blocks_written[2];	/* total blocks written (64 bit) */
	__be32 words_written[2];	/* total words written (64 bit) */
पूर्ण;

काष्ठा wm_adsp_compr;

काष्ठा wm_adsp_compr_buf अणु
	काष्ठा list_head list;
	काष्ठा wm_adsp *dsp;
	काष्ठा wm_adsp_compr *compr;

	काष्ठा wm_adsp_buffer_region *regions;
	u32 host_buf_ptr;

	u32 error;
	u32 irq_count;
	पूर्णांक पढ़ो_index;
	पूर्णांक avail;
	पूर्णांक host_buf_mem_type;

	अक्षर *name;
पूर्ण;

काष्ठा wm_adsp_compr अणु
	काष्ठा list_head list;
	काष्ठा wm_adsp *dsp;
	काष्ठा wm_adsp_compr_buf *buf;

	काष्ठा snd_compr_stream *stream;
	काष्ठा snd_compressed_buffer size;

	u32 *raw_buf;
	अचिन्हित पूर्णांक copied_total;

	अचिन्हित पूर्णांक sample_rate;

	स्थिर अक्षर *name;
पूर्ण;

#घोषणा WM_ADSP_DATA_WORD_SIZE         3

#घोषणा WM_ADSP_MIN_FRAGMENTS          1
#घोषणा WM_ADSP_MAX_FRAGMENTS          256
#घोषणा WM_ADSP_MIN_FRAGMENT_SIZE      (64 * WM_ADSP_DATA_WORD_SIZE)
#घोषणा WM_ADSP_MAX_FRAGMENT_SIZE      (4096 * WM_ADSP_DATA_WORD_SIZE)

#घोषणा WM_ADSP_ALG_XM_STRUCT_MAGIC    0x49aec7

#घोषणा HOST_BUFFER_FIELD(field) \
	(दुरत्व(काष्ठा wm_adsp_buffer, field) / माप(__be32))

#घोषणा ALG_XM_FIELD(field) \
	(दुरत्व(काष्ठा wm_adsp_alg_xm_काष्ठा, field) / माप(__be32))

#घोषणा HOST_BUF_COEFF_SUPPORTED_COMPAT_VER	1

#घोषणा HOST_BUF_COEFF_COMPAT_VER_MASK		0xFF00
#घोषणा HOST_BUF_COEFF_COMPAT_VER_SHIFT		8

अटल पूर्णांक wm_adsp_buffer_init(काष्ठा wm_adsp *dsp);
अटल पूर्णांक wm_adsp_buffer_मुक्त(काष्ठा wm_adsp *dsp);

काष्ठा wm_adsp_buffer_region अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक cumulative_size;
	अचिन्हित पूर्णांक mem_type;
	अचिन्हित पूर्णांक base_addr;
पूर्ण;

काष्ठा wm_adsp_buffer_region_def अणु
	अचिन्हित पूर्णांक mem_type;
	अचिन्हित पूर्णांक base_offset;
	अचिन्हित पूर्णांक size_offset;
पूर्ण;

अटल स्थिर काष्ठा wm_adsp_buffer_region_def शेष_regions[] = अणु
	अणु
		.mem_type = WMFW_ADSP2_XM,
		.base_offset = HOST_BUFFER_FIELD(buf1_base),
		.size_offset = HOST_BUFFER_FIELD(buf1_size),
	पूर्ण,
	अणु
		.mem_type = WMFW_ADSP2_XM,
		.base_offset = HOST_BUFFER_FIELD(buf2_base),
		.size_offset = HOST_BUFFER_FIELD(buf1_buf2_size),
	पूर्ण,
	अणु
		.mem_type = WMFW_ADSP2_YM,
		.base_offset = HOST_BUFFER_FIELD(buf3_base),
		.size_offset = HOST_BUFFER_FIELD(buf_total_size),
	पूर्ण,
पूर्ण;

काष्ठा wm_adsp_fw_caps अणु
	u32 id;
	काष्ठा snd_codec_desc desc;
	पूर्णांक num_regions;
	स्थिर काष्ठा wm_adsp_buffer_region_def *region_defs;
पूर्ण;

अटल स्थिर काष्ठा wm_adsp_fw_caps ctrl_caps[] = अणु
	अणु
		.id = SND_AUDIOCODEC_BESPOKE,
		.desc = अणु
			.max_ch = 8,
			.sample_rates = अणु 16000 पूर्ण,
			.num_sample_rates = 1,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.num_regions = ARRAY_SIZE(शेष_regions),
		.region_defs = शेष_regions,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wm_adsp_fw_caps trace_caps[] = अणु
	अणु
		.id = SND_AUDIOCODEC_BESPOKE,
		.desc = अणु
			.max_ch = 8,
			.sample_rates = अणु
				4000, 8000, 11025, 12000, 16000, 22050,
				24000, 32000, 44100, 48000, 64000, 88200,
				96000, 176400, 192000
			पूर्ण,
			.num_sample_rates = 15,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.num_regions = ARRAY_SIZE(शेष_regions),
		.region_defs = शेष_regions,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *file;
	पूर्णांक compr_direction;
	पूर्णांक num_caps;
	स्थिर काष्ठा wm_adsp_fw_caps *caps;
	bool voice_trigger;
पूर्ण wm_adsp_fw[WM_ADSP_NUM_FW] = अणु
	[WM_ADSP_FW_MBC_VSS] =  अणु .file = "mbc-vss" पूर्ण,
	[WM_ADSP_FW_HIFI] =     अणु .file = "hifi" पूर्ण,
	[WM_ADSP_FW_TX] =       अणु .file = "tx" पूर्ण,
	[WM_ADSP_FW_TX_SPK] =   अणु .file = "tx-spk" पूर्ण,
	[WM_ADSP_FW_RX] =       अणु .file = "rx" पूर्ण,
	[WM_ADSP_FW_RX_ANC] =   अणु .file = "rx-anc" पूर्ण,
	[WM_ADSP_FW_CTRL] =     अणु
		.file = "ctrl",
		.compr_direction = SND_COMPRESS_CAPTURE,
		.num_caps = ARRAY_SIZE(ctrl_caps),
		.caps = ctrl_caps,
		.voice_trigger = true,
	पूर्ण,
	[WM_ADSP_FW_ASR] =      अणु .file = "asr" पूर्ण,
	[WM_ADSP_FW_TRACE] =    अणु
		.file = "trace",
		.compr_direction = SND_COMPRESS_CAPTURE,
		.num_caps = ARRAY_SIZE(trace_caps),
		.caps = trace_caps,
	पूर्ण,
	[WM_ADSP_FW_SPK_PROT] = अणु .file = "spk-prot" पूर्ण,
	[WM_ADSP_FW_SPK_CALI] = अणु .file = "spk-cali" पूर्ण,
	[WM_ADSP_FW_SPK_DIAG] = अणु .file = "spk-diag" पूर्ण,
	[WM_ADSP_FW_MISC] =     अणु .file = "misc" पूर्ण,
पूर्ण;

काष्ठा wm_coeff_ctl अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *fw_name;
	/* Subname is needed to match with firmware */
	स्थिर अक्षर *subname;
	अचिन्हित पूर्णांक subname_len;
	काष्ठा wm_adsp_alg_region alg_region;
	काष्ठा wm_adsp *dsp;
	अचिन्हित पूर्णांक enabled:1;
	काष्ठा list_head list;
	व्योम *cache;
	अचिन्हित पूर्णांक offset;
	माप_प्रकार len;
	अचिन्हित पूर्णांक set:1;
	काष्ठा soc_bytes_ext bytes_ext;
	अचिन्हित पूर्णांक flags;
	snd_ctl_elem_type_t type;
पूर्ण;

अटल स्थिर अक्षर *wm_adsp_mem_region_name(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल WMFW_ADSP1_PM:
		वापस "PM";
	हाल WMFW_HALO_PM_PACKED:
		वापस "PM_PACKED";
	हाल WMFW_ADSP1_DM:
		वापस "DM";
	हाल WMFW_ADSP2_XM:
		वापस "XM";
	हाल WMFW_HALO_XM_PACKED:
		वापस "XM_PACKED";
	हाल WMFW_ADSP2_YM:
		वापस "YM";
	हाल WMFW_HALO_YM_PACKED:
		वापस "YM_PACKED";
	हाल WMFW_ADSP1_ZM:
		वापस "ZM";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम wm_adsp_debugfs_save_wmfwname(काष्ठा wm_adsp *dsp, स्थिर अक्षर *s)
अणु
	अक्षर *पंचांगp = kaप्र_लिखो(GFP_KERNEL, "%s\n", s);

	kमुक्त(dsp->wmfw_file_name);
	dsp->wmfw_file_name = पंचांगp;
पूर्ण

अटल व्योम wm_adsp_debugfs_save_binname(काष्ठा wm_adsp *dsp, स्थिर अक्षर *s)
अणु
	अक्षर *पंचांगp = kaप्र_लिखो(GFP_KERNEL, "%s\n", s);

	kमुक्त(dsp->bin_file_name);
	dsp->bin_file_name = पंचांगp;
पूर्ण

अटल व्योम wm_adsp_debugfs_clear(काष्ठा wm_adsp *dsp)
अणु
	kमुक्त(dsp->wmfw_file_name);
	kमुक्त(dsp->bin_file_name);
	dsp->wmfw_file_name = शून्य;
	dsp->bin_file_name = शून्य;
पूर्ण

अटल sमाप_प्रकार wm_adsp_debugfs_wmfw_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wm_adsp *dsp = file->निजी_data;
	sमाप_प्रकार ret;

	mutex_lock(&dsp->pwr_lock);

	अगर (!dsp->wmfw_file_name || !dsp->booted)
		ret = 0;
	अन्यथा
		ret = simple_पढ़ो_from_buffer(user_buf, count, ppos,
					      dsp->wmfw_file_name,
					      म_माप(dsp->wmfw_file_name));

	mutex_unlock(&dsp->pwr_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार wm_adsp_debugfs_bin_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wm_adsp *dsp = file->निजी_data;
	sमाप_प्रकार ret;

	mutex_lock(&dsp->pwr_lock);

	अगर (!dsp->bin_file_name || !dsp->booted)
		ret = 0;
	अन्यथा
		ret = simple_पढ़ो_from_buffer(user_buf, count, ppos,
					      dsp->bin_file_name,
					      म_माप(dsp->bin_file_name));

	mutex_unlock(&dsp->pwr_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations fops;
पूर्ण wm_adsp_debugfs_fops[] = अणु
	अणु
		.name = "wmfw_file_name",
		.fops = अणु
			.खोलो = simple_खोलो,
			.पढ़ो = wm_adsp_debugfs_wmfw_पढ़ो,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "bin_file_name",
		.fops = अणु
			.खोलो = simple_खोलो,
			.पढ़ो = wm_adsp_debugfs_bin_पढ़ो,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम wm_adsp2_init_debugfs(काष्ठा wm_adsp *dsp,
				  काष्ठा snd_soc_component *component)
अणु
	काष्ठा dentry *root = शून्य;
	पूर्णांक i;

	root = debugfs_create_dir(dsp->name, component->debugfs_root);

	debugfs_create_bool("booted", 0444, root, &dsp->booted);
	debugfs_create_bool("running", 0444, root, &dsp->running);
	debugfs_create_x32("fw_id", 0444, root, &dsp->fw_id);
	debugfs_create_x32("fw_version", 0444, root, &dsp->fw_id_version);

	क्रम (i = 0; i < ARRAY_SIZE(wm_adsp_debugfs_fops); ++i)
		debugfs_create_file(wm_adsp_debugfs_fops[i].name, 0444, root,
				    dsp, &wm_adsp_debugfs_fops[i].fops);

	dsp->debugfs_root = root;
पूर्ण

अटल व्योम wm_adsp2_cleanup_debugfs(काष्ठा wm_adsp *dsp)
अणु
	wm_adsp_debugfs_clear(dsp);
	debugfs_हटाओ_recursive(dsp->debugfs_root);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम wm_adsp2_init_debugfs(काष्ठा wm_adsp *dsp,
					 काष्ठा snd_soc_component *component)
अणु
पूर्ण

अटल अंतरभूत व्योम wm_adsp2_cleanup_debugfs(काष्ठा wm_adsp *dsp)
अणु
पूर्ण

अटल अंतरभूत व्योम wm_adsp_debugfs_save_wmfwname(काष्ठा wm_adsp *dsp,
						 स्थिर अक्षर *s)
अणु
पूर्ण

अटल अंतरभूत व्योम wm_adsp_debugfs_save_binname(काष्ठा wm_adsp *dsp,
						स्थिर अक्षर *s)
अणु
पूर्ण

अटल अंतरभूत व्योम wm_adsp_debugfs_clear(काष्ठा wm_adsp *dsp)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक wm_adsp_fw_get(काष्ठा snd_kcontrol *kcontrol,
		   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा wm_adsp *dsp = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = dsp[e->shअगरt_l].fw;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_fw_get);

पूर्णांक wm_adsp_fw_put(काष्ठा snd_kcontrol *kcontrol,
		   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा wm_adsp *dsp = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	अगर (ucontrol->value.क्रमागतerated.item[0] == dsp[e->shअगरt_l].fw)
		वापस 0;

	अगर (ucontrol->value.क्रमागतerated.item[0] >= WM_ADSP_NUM_FW)
		वापस -EINVAL;

	mutex_lock(&dsp[e->shअगरt_l].pwr_lock);

	अगर (dsp[e->shअगरt_l].booted || !list_empty(&dsp[e->shअगरt_l].compr_list))
		ret = -EBUSY;
	अन्यथा
		dsp[e->shअगरt_l].fw = ucontrol->value.क्रमागतerated.item[0];

	mutex_unlock(&dsp[e->shअगरt_l].pwr_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_fw_put);

स्थिर काष्ठा soc_क्रमागत wm_adsp_fw_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(0, 0, ARRAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGLE(0, 1, ARRAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGLE(0, 2, ARRAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGLE(0, 3, ARRAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGLE(0, 4, ARRAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGLE(0, 5, ARRAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGLE(0, 6, ARRAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
पूर्ण;
EXPORT_SYMBOL_GPL(wm_adsp_fw_क्रमागत);

अटल काष्ठा wm_adsp_region स्थिर *wm_adsp_find_region(काष्ठा wm_adsp *dsp,
							पूर्णांक type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dsp->num_mems; i++)
		अगर (dsp->mem[i].type == type)
			वापस &dsp->mem[i];

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक wm_adsp_region_to_reg(काष्ठा wm_adsp_region स्थिर *mem,
					  अचिन्हित पूर्णांक offset)
अणु
	चयन (mem->type) अणु
	हाल WMFW_ADSP1_PM:
		वापस mem->base + (offset * 3);
	हाल WMFW_ADSP1_DM:
	हाल WMFW_ADSP2_XM:
	हाल WMFW_ADSP2_YM:
	हाल WMFW_ADSP1_ZM:
		वापस mem->base + (offset * 2);
	शेष:
		WARN(1, "Unknown memory region type");
		वापस offset;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक wm_halo_region_to_reg(काष्ठा wm_adsp_region स्थिर *mem,
					  अचिन्हित पूर्णांक offset)
अणु
	चयन (mem->type) अणु
	हाल WMFW_ADSP2_XM:
	हाल WMFW_ADSP2_YM:
		वापस mem->base + (offset * 4);
	हाल WMFW_HALO_XM_PACKED:
	हाल WMFW_HALO_YM_PACKED:
		वापस (mem->base + (offset * 3)) & ~0x3;
	हाल WMFW_HALO_PM_PACKED:
		वापस mem->base + (offset * 5);
	शेष:
		WARN(1, "Unknown memory region type");
		वापस offset;
	पूर्ण
पूर्ण

अटल व्योम wm_adsp_पढ़ो_fw_status(काष्ठा wm_adsp *dsp,
				   पूर्णांक noffs, अचिन्हित पूर्णांक *offs)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < noffs; ++i) अणु
		ret = regmap_पढ़ो(dsp->regmap, dsp->base + offs[i], &offs[i]);
		अगर (ret) अणु
			adsp_err(dsp, "Failed to read SCRATCH%u: %d\n", i, ret);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wm_adsp2_show_fw_status(काष्ठा wm_adsp *dsp)
अणु
	अचिन्हित पूर्णांक offs[] = अणु
		ADSP2_SCRATCH0, ADSP2_SCRATCH1, ADSP2_SCRATCH2, ADSP2_SCRATCH3,
	पूर्ण;

	wm_adsp_पढ़ो_fw_status(dsp, ARRAY_SIZE(offs), offs);

	adsp_dbg(dsp, "FW SCRATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		 offs[0], offs[1], offs[2], offs[3]);
पूर्ण

अटल व्योम wm_adsp2v2_show_fw_status(काष्ठा wm_adsp *dsp)
अणु
	अचिन्हित पूर्णांक offs[] = अणु ADSP2V2_SCRATCH0_1, ADSP2V2_SCRATCH2_3 पूर्ण;

	wm_adsp_पढ़ो_fw_status(dsp, ARRAY_SIZE(offs), offs);

	adsp_dbg(dsp, "FW SCRATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		 offs[0] & 0xFFFF, offs[0] >> 16,
		 offs[1] & 0xFFFF, offs[1] >> 16);
पूर्ण

अटल व्योम wm_halo_show_fw_status(काष्ठा wm_adsp *dsp)
अणु
	अचिन्हित पूर्णांक offs[] = अणु
		HALO_SCRATCH1, HALO_SCRATCH2, HALO_SCRATCH3, HALO_SCRATCH4,
	पूर्ण;

	wm_adsp_पढ़ो_fw_status(dsp, ARRAY_SIZE(offs), offs);

	adsp_dbg(dsp, "FW SCRATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		 offs[0], offs[1], offs[2], offs[3]);
पूर्ण

अटल अंतरभूत काष्ठा wm_coeff_ctl *bytes_ext_to_ctl(काष्ठा soc_bytes_ext *ext)
अणु
	वापस container_of(ext, काष्ठा wm_coeff_ctl, bytes_ext);
पूर्ण

अटल पूर्णांक wm_coeff_base_reg(काष्ठा wm_coeff_ctl *ctl, अचिन्हित पूर्णांक *reg)
अणु
	स्थिर काष्ठा wm_adsp_alg_region *alg_region = &ctl->alg_region;
	काष्ठा wm_adsp *dsp = ctl->dsp;
	स्थिर काष्ठा wm_adsp_region *mem;

	mem = wm_adsp_find_region(dsp, alg_region->type);
	अगर (!mem) अणु
		adsp_err(dsp, "No base for region %x\n",
			 alg_region->type);
		वापस -EINVAL;
	पूर्ण

	*reg = dsp->ops->region_to_reg(mem, ctl->alg_region.base + ctl->offset);

	वापस 0;
पूर्ण

अटल पूर्णांक wm_coeff_info(काष्ठा snd_kcontrol *kctl,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा soc_bytes_ext *bytes_ext =
		(काष्ठा soc_bytes_ext *)kctl->निजी_value;
	काष्ठा wm_coeff_ctl *ctl = bytes_ext_to_ctl(bytes_ext);

	चयन (ctl->type) अणु
	हाल WMFW_CTL_TYPE_ACKED:
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->value.पूर्णांकeger.min = WM_ADSP_ACKED_CTL_MIN_VALUE;
		uinfo->value.पूर्णांकeger.max = WM_ADSP_ACKED_CTL_MAX_VALUE;
		uinfo->value.पूर्णांकeger.step = 1;
		uinfo->count = 1;
		अवरोध;
	शेष:
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
		uinfo->count = ctl->len;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm_coeff_ग_लिखो_acked_control(काष्ठा wm_coeff_ctl *ctl,
					अचिन्हित पूर्णांक event_id)
अणु
	काष्ठा wm_adsp *dsp = ctl->dsp;
	__be32 val = cpu_to_be32(event_id);
	अचिन्हित पूर्णांक reg;
	पूर्णांक i, ret;

	ret = wm_coeff_base_reg(ctl, &reg);
	अगर (ret)
		वापस ret;

	adsp_dbg(dsp, "Sending 0x%x to acked control alg 0x%x %s:0x%x\n",
		 event_id, ctl->alg_region.alg,
		 wm_adsp_mem_region_name(ctl->alg_region.type), ctl->offset);

	ret = regmap_raw_ग_लिखो(dsp->regmap, reg, &val, माप(val));
	अगर (ret) अणु
		adsp_err(dsp, "Failed to write %x: %d\n", reg, ret);
		वापस ret;
	पूर्ण

	/*
	 * Poll क्रम ack, we initially poll at ~1ms पूर्णांकervals क्रम firmwares
	 * that respond quickly, then go to ~10ms polls. A firmware is unlikely
	 * to ack instantly so we करो the first 1ms delay beक्रमe पढ़ोing the
	 * control to aव्योम a poपूर्णांकless bus transaction
	 */
	क्रम (i = 0; i < WM_ADSP_ACKED_CTL_TIMEOUT_MS;) अणु
		चयन (i) अणु
		हाल 0 ... WM_ADSP_ACKED_CTL_N_QUICKPOLLS - 1:
			usleep_range(1000, 2000);
			i++;
			अवरोध;
		शेष:
			usleep_range(10000, 20000);
			i += 10;
			अवरोध;
		पूर्ण

		ret = regmap_raw_पढ़ो(dsp->regmap, reg, &val, माप(val));
		अगर (ret) अणु
			adsp_err(dsp, "Failed to read %x: %d\n", reg, ret);
			वापस ret;
		पूर्ण

		अगर (val == 0) अणु
			adsp_dbg(dsp, "Acked control ACKED at poll %u\n", i);
			वापस 0;
		पूर्ण
	पूर्ण

	adsp_warn(dsp, "Acked control @0x%x alg:0x%x %s:0x%x timed out\n",
		  reg, ctl->alg_region.alg,
		  wm_adsp_mem_region_name(ctl->alg_region.type),
		  ctl->offset);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक wm_coeff_ग_लिखो_ctrl_raw(काष्ठा wm_coeff_ctl *ctl,
				   स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wm_adsp *dsp = ctl->dsp;
	व्योम *scratch;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	ret = wm_coeff_base_reg(ctl, &reg);
	अगर (ret)
		वापस ret;

	scratch = kmemdup(buf, len, GFP_KERNEL | GFP_DMA);
	अगर (!scratch)
		वापस -ENOMEM;

	ret = regmap_raw_ग_लिखो(dsp->regmap, reg, scratch,
			       len);
	अगर (ret) अणु
		adsp_err(dsp, "Failed to write %zu bytes to %x: %d\n",
			 len, reg, ret);
		kमुक्त(scratch);
		वापस ret;
	पूर्ण
	adsp_dbg(dsp, "Wrote %zu bytes to %x\n", len, reg);

	kमुक्त(scratch);

	वापस 0;
पूर्ण

अटल पूर्णांक wm_coeff_ग_लिखो_ctrl(काष्ठा wm_coeff_ctl *ctl,
			       स्थिर व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret = 0;

	अगर (ctl->flags & WMFW_CTL_FLAG_VOLATILE)
		ret = -EPERM;
	अन्यथा अगर (buf != ctl->cache)
		स_नकल(ctl->cache, buf, len);

	ctl->set = 1;
	अगर (ctl->enabled && ctl->dsp->running)
		ret = wm_coeff_ग_लिखो_ctrl_raw(ctl, buf, len);

	वापस ret;
पूर्ण

अटल पूर्णांक wm_coeff_put(काष्ठा snd_kcontrol *kctl,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_bytes_ext *bytes_ext =
		(काष्ठा soc_bytes_ext *)kctl->निजी_value;
	काष्ठा wm_coeff_ctl *ctl = bytes_ext_to_ctl(bytes_ext);
	अक्षर *p = ucontrol->value.bytes.data;
	पूर्णांक ret = 0;

	mutex_lock(&ctl->dsp->pwr_lock);
	ret = wm_coeff_ग_लिखो_ctrl(ctl, p, ctl->len);
	mutex_unlock(&ctl->dsp->pwr_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wm_coeff_tlv_put(काष्ठा snd_kcontrol *kctl,
			    स्थिर अचिन्हित पूर्णांक __user *bytes, अचिन्हित पूर्णांक size)
अणु
	काष्ठा soc_bytes_ext *bytes_ext =
		(काष्ठा soc_bytes_ext *)kctl->निजी_value;
	काष्ठा wm_coeff_ctl *ctl = bytes_ext_to_ctl(bytes_ext);
	पूर्णांक ret = 0;

	mutex_lock(&ctl->dsp->pwr_lock);

	अगर (copy_from_user(ctl->cache, bytes, size))
		ret = -EFAULT;
	अन्यथा
		ret = wm_coeff_ग_लिखो_ctrl(ctl, ctl->cache, size);

	mutex_unlock(&ctl->dsp->pwr_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wm_coeff_put_acked(काष्ठा snd_kcontrol *kctl,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_bytes_ext *bytes_ext =
		(काष्ठा soc_bytes_ext *)kctl->निजी_value;
	काष्ठा wm_coeff_ctl *ctl = bytes_ext_to_ctl(bytes_ext);
	अचिन्हित पूर्णांक val = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक ret;

	अगर (val == 0)
		वापस 0;	/* 0 means no event */

	mutex_lock(&ctl->dsp->pwr_lock);

	अगर (ctl->enabled && ctl->dsp->running)
		ret = wm_coeff_ग_लिखो_acked_control(ctl, val);
	अन्यथा
		ret = -EPERM;

	mutex_unlock(&ctl->dsp->pwr_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wm_coeff_पढ़ो_ctrl_raw(काष्ठा wm_coeff_ctl *ctl,
				  व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wm_adsp *dsp = ctl->dsp;
	व्योम *scratch;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	ret = wm_coeff_base_reg(ctl, &reg);
	अगर (ret)
		वापस ret;

	scratch = kदो_स्मृति(len, GFP_KERNEL | GFP_DMA);
	अगर (!scratch)
		वापस -ENOMEM;

	ret = regmap_raw_पढ़ो(dsp->regmap, reg, scratch, len);
	अगर (ret) अणु
		adsp_err(dsp, "Failed to read %zu bytes from %x: %d\n",
			 len, reg, ret);
		kमुक्त(scratch);
		वापस ret;
	पूर्ण
	adsp_dbg(dsp, "Read %zu bytes from %x\n", len, reg);

	स_नकल(buf, scratch, len);
	kमुक्त(scratch);

	वापस 0;
पूर्ण

अटल पूर्णांक wm_coeff_पढ़ो_ctrl(काष्ठा wm_coeff_ctl *ctl, व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret = 0;

	अगर (ctl->flags & WMFW_CTL_FLAG_VOLATILE) अणु
		अगर (ctl->enabled && ctl->dsp->running)
			वापस wm_coeff_पढ़ो_ctrl_raw(ctl, buf, len);
		अन्यथा
			वापस -EPERM;
	पूर्ण अन्यथा अणु
		अगर (!ctl->flags && ctl->enabled && ctl->dsp->running)
			ret = wm_coeff_पढ़ो_ctrl_raw(ctl, ctl->cache, ctl->len);

		अगर (buf != ctl->cache)
			स_नकल(buf, ctl->cache, len);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wm_coeff_get(काष्ठा snd_kcontrol *kctl,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_bytes_ext *bytes_ext =
		(काष्ठा soc_bytes_ext *)kctl->निजी_value;
	काष्ठा wm_coeff_ctl *ctl = bytes_ext_to_ctl(bytes_ext);
	अक्षर *p = ucontrol->value.bytes.data;
	पूर्णांक ret;

	mutex_lock(&ctl->dsp->pwr_lock);
	ret = wm_coeff_पढ़ो_ctrl(ctl, p, ctl->len);
	mutex_unlock(&ctl->dsp->pwr_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wm_coeff_tlv_get(काष्ठा snd_kcontrol *kctl,
			    अचिन्हित पूर्णांक __user *bytes, अचिन्हित पूर्णांक size)
अणु
	काष्ठा soc_bytes_ext *bytes_ext =
		(काष्ठा soc_bytes_ext *)kctl->निजी_value;
	काष्ठा wm_coeff_ctl *ctl = bytes_ext_to_ctl(bytes_ext);
	पूर्णांक ret = 0;

	mutex_lock(&ctl->dsp->pwr_lock);

	ret = wm_coeff_पढ़ो_ctrl_raw(ctl, ctl->cache, size);

	अगर (!ret && copy_to_user(bytes, ctl->cache, size))
		ret = -EFAULT;

	mutex_unlock(&ctl->dsp->pwr_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wm_coeff_get_acked(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/*
	 * Although it's not useful to पढ़ो an acked control, we must satisfy
	 * user-side assumptions that all controls are पढ़ोable and that a
	 * ग_लिखो of the same value should be filtered out (it's valid to send
	 * the same event number again to the firmware). We thereक्रमe वापस 0,
	 * meaning "no event" so valid event numbers will always be a change
	 */
	ucontrol->value.पूर्णांकeger.value[0] = 0;

	वापस 0;
पूर्ण

काष्ठा wmfw_ctl_work अणु
	काष्ठा wm_adsp *dsp;
	काष्ठा wm_coeff_ctl *ctl;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल अचिन्हित पूर्णांक wmfw_convert_flags(अचिन्हित पूर्णांक in, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक out, rd, wr, vol;

	अगर (len > ADSP_MAX_STD_CTRL_SIZE) अणु
		rd = SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		wr = SNDRV_CTL_ELEM_ACCESS_TLV_WRITE;
		vol = SNDRV_CTL_ELEM_ACCESS_VOLATILE;

		out = SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK;
	पूर्ण अन्यथा अणु
		rd = SNDRV_CTL_ELEM_ACCESS_READ;
		wr = SNDRV_CTL_ELEM_ACCESS_WRITE;
		vol = SNDRV_CTL_ELEM_ACCESS_VOLATILE;

		out = 0;
	पूर्ण

	अगर (in) अणु
		out |= rd;
		अगर (in & WMFW_CTL_FLAG_WRITEABLE)
			out |= wr;
		अगर (in & WMFW_CTL_FLAG_VOLATILE)
			out |= vol;
	पूर्ण अन्यथा अणु
		out |= rd | wr | vol;
	पूर्ण

	वापस out;
पूर्ण

अटल पूर्णांक wmfw_add_ctl(काष्ठा wm_adsp *dsp, काष्ठा wm_coeff_ctl *ctl)
अणु
	काष्ठा snd_kcontrol_new *kcontrol;
	पूर्णांक ret;

	अगर (!ctl || !ctl->name)
		वापस -EINVAL;

	kcontrol = kzalloc(माप(*kcontrol), GFP_KERNEL);
	अगर (!kcontrol)
		वापस -ENOMEM;

	kcontrol->name = ctl->name;
	kcontrol->info = wm_coeff_info;
	kcontrol->अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	kcontrol->tlv.c = snd_soc_bytes_tlv_callback;
	kcontrol->निजी_value = (अचिन्हित दीर्घ)&ctl->bytes_ext;
	kcontrol->access = wmfw_convert_flags(ctl->flags, ctl->len);

	चयन (ctl->type) अणु
	हाल WMFW_CTL_TYPE_ACKED:
		kcontrol->get = wm_coeff_get_acked;
		kcontrol->put = wm_coeff_put_acked;
		अवरोध;
	शेष:
		अगर (kcontrol->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) अणु
			ctl->bytes_ext.max = ctl->len;
			ctl->bytes_ext.get = wm_coeff_tlv_get;
			ctl->bytes_ext.put = wm_coeff_tlv_put;
		पूर्ण अन्यथा अणु
			kcontrol->get = wm_coeff_get;
			kcontrol->put = wm_coeff_put;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = snd_soc_add_component_controls(dsp->component, kcontrol, 1);
	अगर (ret < 0)
		जाओ err_kcontrol;

	kमुक्त(kcontrol);

	वापस 0;

err_kcontrol:
	kमुक्त(kcontrol);
	वापस ret;
पूर्ण

अटल पूर्णांक wm_coeff_init_control_caches(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_coeff_ctl *ctl;
	पूर्णांक ret;

	list_क्रम_each_entry(ctl, &dsp->ctl_list, list) अणु
		अगर (!ctl->enabled || ctl->set)
			जारी;
		अगर (ctl->flags & WMFW_CTL_FLAG_VOLATILE)
			जारी;

		/*
		 * For पढ़ोable controls populate the cache from the DSP memory.
		 * For non-पढ़ोable controls the cache was zero-filled when
		 * created so we करोn't need to करो anything.
		 */
		अगर (!ctl->flags || (ctl->flags & WMFW_CTL_FLAG_READABLE)) अणु
			ret = wm_coeff_पढ़ो_ctrl_raw(ctl, ctl->cache, ctl->len);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm_coeff_sync_controls(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_coeff_ctl *ctl;
	पूर्णांक ret;

	list_क्रम_each_entry(ctl, &dsp->ctl_list, list) अणु
		अगर (!ctl->enabled)
			जारी;
		अगर (ctl->set && !(ctl->flags & WMFW_CTL_FLAG_VOLATILE)) अणु
			ret = wm_coeff_ग_लिखो_ctrl_raw(ctl, ctl->cache,
						      ctl->len);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wm_adsp_संकेत_event_controls(काष्ठा wm_adsp *dsp,
					  अचिन्हित पूर्णांक event)
अणु
	काष्ठा wm_coeff_ctl *ctl;
	पूर्णांक ret;

	list_क्रम_each_entry(ctl, &dsp->ctl_list, list) अणु
		अगर (ctl->type != WMFW_CTL_TYPE_HOSTEVENT)
			जारी;

		अगर (!ctl->enabled)
			जारी;

		ret = wm_coeff_ग_लिखो_acked_control(ctl, event);
		अगर (ret)
			adsp_warn(dsp,
				  "Failed to send 0x%x event to alg 0x%x (%d)\n",
				  event, ctl->alg_region.alg, ret);
	पूर्ण
पूर्ण

अटल व्योम wm_adsp_ctl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wmfw_ctl_work *ctl_work = container_of(work,
						      काष्ठा wmfw_ctl_work,
						      work);

	wmfw_add_ctl(ctl_work->dsp, ctl_work->ctl);
	kमुक्त(ctl_work);
पूर्ण

अटल व्योम wm_adsp_मुक्त_ctl_blk(काष्ठा wm_coeff_ctl *ctl)
अणु
	kमुक्त(ctl->cache);
	kमुक्त(ctl->name);
	kमुक्त(ctl->subname);
	kमुक्त(ctl);
पूर्ण

अटल पूर्णांक wm_adsp_create_control(काष्ठा wm_adsp *dsp,
				  स्थिर काष्ठा wm_adsp_alg_region *alg_region,
				  अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len,
				  स्थिर अक्षर *subname, अचिन्हित पूर्णांक subname_len,
				  अचिन्हित पूर्णांक flags, snd_ctl_elem_type_t type)
अणु
	काष्ठा wm_coeff_ctl *ctl;
	काष्ठा wmfw_ctl_work *ctl_work;
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	स्थिर अक्षर *region_name;
	पूर्णांक ret;

	region_name = wm_adsp_mem_region_name(alg_region->type);
	अगर (!region_name) अणु
		adsp_err(dsp, "Unknown region type: %d\n", alg_region->type);
		वापस -EINVAL;
	पूर्ण

	चयन (dsp->fw_ver) अणु
	हाल 0:
	हाल 1:
		snम_लिखो(name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN, "%s %s %x",
			 dsp->name, region_name, alg_region->alg);
		subname = शून्य; /* करोn't append subname */
		अवरोध;
	हाल 2:
		ret = scnम_लिखो(name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN,
				"%s%c %.12s %x", dsp->name, *region_name,
				wm_adsp_fw_text[dsp->fw], alg_region->alg);
		अवरोध;
	शेष:
		ret = scnम_लिखो(name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN,
				"%s %.12s %x", dsp->name,
				wm_adsp_fw_text[dsp->fw], alg_region->alg);
		अवरोध;
	पूर्ण

	अगर (subname) अणु
		पूर्णांक avail = SNDRV_CTL_ELEM_ID_NAME_MAXLEN - ret - 2;
		पूर्णांक skip = 0;

		अगर (dsp->component->name_prefix)
			avail -= म_माप(dsp->component->name_prefix) + 1;

		/* Truncate the subname from the start अगर it is too दीर्घ */
		अगर (subname_len > avail)
			skip = subname_len - avail;

		snम_लिखो(name + ret, SNDRV_CTL_ELEM_ID_NAME_MAXLEN - ret,
			 " %.*s", subname_len - skip, subname + skip);
	पूर्ण

	list_क्रम_each_entry(ctl, &dsp->ctl_list, list) अणु
		अगर (!म_भेद(ctl->name, name)) अणु
			अगर (!ctl->enabled)
				ctl->enabled = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	ctl = kzalloc(माप(*ctl), GFP_KERNEL);
	अगर (!ctl)
		वापस -ENOMEM;
	ctl->fw_name = wm_adsp_fw_text[dsp->fw];
	ctl->alg_region = *alg_region;
	ctl->name = kmemdup(name, म_माप(name) + 1, GFP_KERNEL);
	अगर (!ctl->name) अणु
		ret = -ENOMEM;
		जाओ err_ctl;
	पूर्ण
	अगर (subname) अणु
		ctl->subname_len = subname_len;
		ctl->subname = kmemdup(subname,
				       म_माप(subname) + 1, GFP_KERNEL);
		अगर (!ctl->subname) अणु
			ret = -ENOMEM;
			जाओ err_ctl_name;
		पूर्ण
	पूर्ण
	ctl->enabled = 1;
	ctl->set = 0;
	ctl->dsp = dsp;

	ctl->flags = flags;
	ctl->type = type;
	ctl->offset = offset;
	ctl->len = len;
	ctl->cache = kzalloc(ctl->len, GFP_KERNEL);
	अगर (!ctl->cache) अणु
		ret = -ENOMEM;
		जाओ err_ctl_subname;
	पूर्ण

	list_add(&ctl->list, &dsp->ctl_list);

	अगर (flags & WMFW_CTL_FLAG_SYS)
		वापस 0;

	ctl_work = kzalloc(माप(*ctl_work), GFP_KERNEL);
	अगर (!ctl_work) अणु
		ret = -ENOMEM;
		जाओ err_list_del;
	पूर्ण

	ctl_work->dsp = dsp;
	ctl_work->ctl = ctl;
	INIT_WORK(&ctl_work->work, wm_adsp_ctl_work);
	schedule_work(&ctl_work->work);

	वापस 0;

err_list_del:
	list_del(&ctl->list);
	kमुक्त(ctl->cache);
err_ctl_subname:
	kमुक्त(ctl->subname);
err_ctl_name:
	kमुक्त(ctl->name);
err_ctl:
	kमुक्त(ctl);

	वापस ret;
पूर्ण

काष्ठा wm_coeff_parsed_alg अणु
	पूर्णांक id;
	स्थिर u8 *name;
	पूर्णांक name_len;
	पूर्णांक ncoeff;
पूर्ण;

काष्ठा wm_coeff_parsed_coeff अणु
	पूर्णांक offset;
	पूर्णांक mem_type;
	स्थिर u8 *name;
	पूर्णांक name_len;
	snd_ctl_elem_type_t ctl_type;
	पूर्णांक flags;
	पूर्णांक len;
पूर्ण;

अटल पूर्णांक wm_coeff_parse_string(पूर्णांक bytes, स्थिर u8 **pos, स्थिर u8 **str)
अणु
	पूर्णांक length;

	चयन (bytes) अणु
	हाल 1:
		length = **pos;
		अवरोध;
	हाल 2:
		length = le16_to_cpu(*((__le16 *)*pos));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (str)
		*str = *pos + bytes;

	*pos += ((length + bytes) + 3) & ~0x03;

	वापस length;
पूर्ण

अटल पूर्णांक wm_coeff_parse_पूर्णांक(पूर्णांक bytes, स्थिर u8 **pos)
अणु
	पूर्णांक val = 0;

	चयन (bytes) अणु
	हाल 2:
		val = le16_to_cpu(*((__le16 *)*pos));
		अवरोध;
	हाल 4:
		val = le32_to_cpu(*((__le32 *)*pos));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	*pos += bytes;

	वापस val;
पूर्ण

अटल अंतरभूत व्योम wm_coeff_parse_alg(काष्ठा wm_adsp *dsp, स्थिर u8 **data,
				      काष्ठा wm_coeff_parsed_alg *blk)
अणु
	स्थिर काष्ठा wmfw_adsp_alg_data *raw;

	चयन (dsp->fw_ver) अणु
	हाल 0:
	हाल 1:
		raw = (स्थिर काष्ठा wmfw_adsp_alg_data *)*data;
		*data = raw->data;

		blk->id = le32_to_cpu(raw->id);
		blk->name = raw->name;
		blk->name_len = म_माप(raw->name);
		blk->ncoeff = le32_to_cpu(raw->ncoeff);
		अवरोध;
	शेष:
		blk->id = wm_coeff_parse_पूर्णांक(माप(raw->id), data);
		blk->name_len = wm_coeff_parse_string(माप(u8), data,
						      &blk->name);
		wm_coeff_parse_string(माप(u16), data, शून्य);
		blk->ncoeff = wm_coeff_parse_पूर्णांक(माप(raw->ncoeff), data);
		अवरोध;
	पूर्ण

	adsp_dbg(dsp, "Algorithm ID: %#x\n", blk->id);
	adsp_dbg(dsp, "Algorithm name: %.*s\n", blk->name_len, blk->name);
	adsp_dbg(dsp, "# of coefficient descriptors: %#x\n", blk->ncoeff);
पूर्ण

अटल अंतरभूत व्योम wm_coeff_parse_coeff(काष्ठा wm_adsp *dsp, स्थिर u8 **data,
					काष्ठा wm_coeff_parsed_coeff *blk)
अणु
	स्थिर काष्ठा wmfw_adsp_coeff_data *raw;
	स्थिर u8 *पंचांगp;
	पूर्णांक length;

	चयन (dsp->fw_ver) अणु
	हाल 0:
	हाल 1:
		raw = (स्थिर काष्ठा wmfw_adsp_coeff_data *)*data;
		*data = *data + माप(raw->hdr) + le32_to_cpu(raw->hdr.size);

		blk->offset = le16_to_cpu(raw->hdr.offset);
		blk->mem_type = le16_to_cpu(raw->hdr.type);
		blk->name = raw->name;
		blk->name_len = म_माप(raw->name);
		blk->ctl_type = (__क्रमce snd_ctl_elem_type_t)le16_to_cpu(raw->ctl_type);
		blk->flags = le16_to_cpu(raw->flags);
		blk->len = le32_to_cpu(raw->len);
		अवरोध;
	शेष:
		पंचांगp = *data;
		blk->offset = wm_coeff_parse_पूर्णांक(माप(raw->hdr.offset), &पंचांगp);
		blk->mem_type = wm_coeff_parse_पूर्णांक(माप(raw->hdr.type), &पंचांगp);
		length = wm_coeff_parse_पूर्णांक(माप(raw->hdr.size), &पंचांगp);
		blk->name_len = wm_coeff_parse_string(माप(u8), &पंचांगp,
						      &blk->name);
		wm_coeff_parse_string(माप(u8), &पंचांगp, शून्य);
		wm_coeff_parse_string(माप(u16), &पंचांगp, शून्य);
		blk->ctl_type =
			(__क्रमce snd_ctl_elem_type_t)wm_coeff_parse_पूर्णांक(माप(raw->ctl_type),
									&पंचांगp);
		blk->flags = wm_coeff_parse_पूर्णांक(माप(raw->flags), &पंचांगp);
		blk->len = wm_coeff_parse_पूर्णांक(माप(raw->len), &पंचांगp);

		*data = *data + माप(raw->hdr) + length;
		अवरोध;
	पूर्ण

	adsp_dbg(dsp, "\tCoefficient type: %#x\n", blk->mem_type);
	adsp_dbg(dsp, "\tCoefficient offset: %#x\n", blk->offset);
	adsp_dbg(dsp, "\tCoefficient name: %.*s\n", blk->name_len, blk->name);
	adsp_dbg(dsp, "\tCoefficient flags: %#x\n", blk->flags);
	adsp_dbg(dsp, "\tALSA control type: %#x\n", blk->ctl_type);
	adsp_dbg(dsp, "\tALSA control len: %#x\n", blk->len);
पूर्ण

अटल पूर्णांक wm_adsp_check_coeff_flags(काष्ठा wm_adsp *dsp,
				स्थिर काष्ठा wm_coeff_parsed_coeff *coeff_blk,
				अचिन्हित पूर्णांक f_required,
				अचिन्हित पूर्णांक f_illegal)
अणु
	अगर ((coeff_blk->flags & f_illegal) ||
	    ((coeff_blk->flags & f_required) != f_required)) अणु
		adsp_err(dsp, "Illegal flags 0x%x for control type 0x%x\n",
			 coeff_blk->flags, coeff_blk->ctl_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm_adsp_parse_coeff(काष्ठा wm_adsp *dsp,
			       स्थिर काष्ठा wmfw_region *region)
अणु
	काष्ठा wm_adsp_alg_region alg_region = अणुपूर्ण;
	काष्ठा wm_coeff_parsed_alg alg_blk;
	काष्ठा wm_coeff_parsed_coeff coeff_blk;
	स्थिर u8 *data = region->data;
	पूर्णांक i, ret;

	wm_coeff_parse_alg(dsp, &data, &alg_blk);
	क्रम (i = 0; i < alg_blk.ncoeff; i++) अणु
		wm_coeff_parse_coeff(dsp, &data, &coeff_blk);

		चयन (coeff_blk.ctl_type) अणु
		हाल SNDRV_CTL_ELEM_TYPE_BYTES:
			अवरोध;
		हाल WMFW_CTL_TYPE_ACKED:
			अगर (coeff_blk.flags & WMFW_CTL_FLAG_SYS)
				जारी;	/* ignore */

			ret = wm_adsp_check_coeff_flags(dsp, &coeff_blk,
						WMFW_CTL_FLAG_VOLATILE |
						WMFW_CTL_FLAG_WRITEABLE |
						WMFW_CTL_FLAG_READABLE,
						0);
			अगर (ret)
				वापस -EINVAL;
			अवरोध;
		हाल WMFW_CTL_TYPE_HOSTEVENT:
			ret = wm_adsp_check_coeff_flags(dsp, &coeff_blk,
						WMFW_CTL_FLAG_SYS |
						WMFW_CTL_FLAG_VOLATILE |
						WMFW_CTL_FLAG_WRITEABLE |
						WMFW_CTL_FLAG_READABLE,
						0);
			अगर (ret)
				वापस -EINVAL;
			अवरोध;
		हाल WMFW_CTL_TYPE_HOST_BUFFER:
			ret = wm_adsp_check_coeff_flags(dsp, &coeff_blk,
						WMFW_CTL_FLAG_SYS |
						WMFW_CTL_FLAG_VOLATILE |
						WMFW_CTL_FLAG_READABLE,
						0);
			अगर (ret)
				वापस -EINVAL;
			अवरोध;
		शेष:
			adsp_err(dsp, "Unknown control type: %d\n",
				 coeff_blk.ctl_type);
			वापस -EINVAL;
		पूर्ण

		alg_region.type = coeff_blk.mem_type;
		alg_region.alg = alg_blk.id;

		ret = wm_adsp_create_control(dsp, &alg_region,
					     coeff_blk.offset,
					     coeff_blk.len,
					     coeff_blk.name,
					     coeff_blk.name_len,
					     coeff_blk.flags,
					     coeff_blk.ctl_type);
		अगर (ret < 0)
			adsp_err(dsp, "Failed to create control: %.*s, %d\n",
				 coeff_blk.name_len, coeff_blk.name, ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक wm_adsp1_parse_sizes(काष्ठा wm_adsp *dsp,
					 स्थिर अक्षर * स्थिर file,
					 अचिन्हित पूर्णांक pos,
					 स्थिर काष्ठा firmware *firmware)
अणु
	स्थिर काष्ठा wmfw_adsp1_sizes *adsp1_sizes;

	adsp1_sizes = (व्योम *)&firmware->data[pos];

	adsp_dbg(dsp, "%s: %d DM, %d PM, %d ZM\n", file,
		 le32_to_cpu(adsp1_sizes->dm), le32_to_cpu(adsp1_sizes->pm),
		 le32_to_cpu(adsp1_sizes->zm));

	वापस pos + माप(*adsp1_sizes);
पूर्ण

अटल अचिन्हित पूर्णांक wm_adsp2_parse_sizes(काष्ठा wm_adsp *dsp,
					 स्थिर अक्षर * स्थिर file,
					 अचिन्हित पूर्णांक pos,
					 स्थिर काष्ठा firmware *firmware)
अणु
	स्थिर काष्ठा wmfw_adsp2_sizes *adsp2_sizes;

	adsp2_sizes = (व्योम *)&firmware->data[pos];

	adsp_dbg(dsp, "%s: %d XM, %d YM %d PM, %d ZM\n", file,
		 le32_to_cpu(adsp2_sizes->xm), le32_to_cpu(adsp2_sizes->ym),
		 le32_to_cpu(adsp2_sizes->pm), le32_to_cpu(adsp2_sizes->zm));

	वापस pos + माप(*adsp2_sizes);
पूर्ण

अटल bool wm_adsp_validate_version(काष्ठा wm_adsp *dsp, अचिन्हित पूर्णांक version)
अणु
	चयन (version) अणु
	हाल 0:
		adsp_warn(dsp, "Deprecated file format %d\n", version);
		वापस true;
	हाल 1:
	हाल 2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm_halo_validate_version(काष्ठा wm_adsp *dsp, अचिन्हित पूर्णांक version)
अणु
	चयन (version) अणु
	हाल 3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm_adsp_load(काष्ठा wm_adsp *dsp)
अणु
	LIST_HEAD(buf_list);
	स्थिर काष्ठा firmware *firmware;
	काष्ठा regmap *regmap = dsp->regmap;
	अचिन्हित पूर्णांक pos = 0;
	स्थिर काष्ठा wmfw_header *header;
	स्थिर काष्ठा wmfw_adsp1_sizes *adsp1_sizes;
	स्थिर काष्ठा wmfw_footer *footer;
	स्थिर काष्ठा wmfw_region *region;
	स्थिर काष्ठा wm_adsp_region *mem;
	स्थिर अक्षर *region_name;
	अक्षर *file, *text = शून्य;
	काष्ठा wm_adsp_buf *buf;
	अचिन्हित पूर्णांक reg;
	पूर्णांक regions = 0;
	पूर्णांक ret, offset, type;

	file = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (file == शून्य)
		वापस -ENOMEM;

	snम_लिखो(file, PAGE_SIZE, "%s-%s-%s.wmfw", dsp->part, dsp->fwf_name,
		 wm_adsp_fw[dsp->fw].file);
	file[PAGE_SIZE - 1] = '\0';

	ret = request_firmware(&firmware, file, dsp->dev);
	अगर (ret != 0) अणु
		adsp_err(dsp, "Failed to request '%s'\n", file);
		जाओ out;
	पूर्ण
	ret = -EINVAL;

	pos = माप(*header) + माप(*adsp1_sizes) + माप(*footer);
	अगर (pos >= firmware->size) अणु
		adsp_err(dsp, "%s: file too short, %zu bytes\n",
			 file, firmware->size);
		जाओ out_fw;
	पूर्ण

	header = (व्योम *)&firmware->data[0];

	अगर (स_भेद(&header->magic[0], "WMFW", 4) != 0) अणु
		adsp_err(dsp, "%s: invalid magic\n", file);
		जाओ out_fw;
	पूर्ण

	अगर (!dsp->ops->validate_version(dsp, header->ver)) अणु
		adsp_err(dsp, "%s: unknown file format %d\n",
			 file, header->ver);
		जाओ out_fw;
	पूर्ण

	adsp_info(dsp, "Firmware version: %d\n", header->ver);
	dsp->fw_ver = header->ver;

	अगर (header->core != dsp->type) अणु
		adsp_err(dsp, "%s: invalid core %d != %d\n",
			 file, header->core, dsp->type);
		जाओ out_fw;
	पूर्ण

	pos = माप(*header);
	pos = dsp->ops->parse_sizes(dsp, file, pos, firmware);

	footer = (व्योम *)&firmware->data[pos];
	pos += माप(*footer);

	अगर (le32_to_cpu(header->len) != pos) अणु
		adsp_err(dsp, "%s: unexpected header length %d\n",
			 file, le32_to_cpu(header->len));
		जाओ out_fw;
	पूर्ण

	adsp_dbg(dsp, "%s: timestamp %llu\n", file,
		 le64_to_cpu(footer->बारtamp));

	जबतक (pos < firmware->size &&
	       माप(*region) < firmware->size - pos) अणु
		region = (व्योम *)&(firmware->data[pos]);
		region_name = "Unknown";
		reg = 0;
		text = शून्य;
		offset = le32_to_cpu(region->offset) & 0xffffff;
		type = be32_to_cpu(region->type) & 0xff;

		चयन (type) अणु
		हाल WMFW_NAME_TEXT:
			region_name = "Firmware name";
			text = kzalloc(le32_to_cpu(region->len) + 1,
				       GFP_KERNEL);
			अवरोध;
		हाल WMFW_ALGORITHM_DATA:
			region_name = "Algorithm";
			ret = wm_adsp_parse_coeff(dsp, region);
			अगर (ret != 0)
				जाओ out_fw;
			अवरोध;
		हाल WMFW_INFO_TEXT:
			region_name = "Information";
			text = kzalloc(le32_to_cpu(region->len) + 1,
				       GFP_KERNEL);
			अवरोध;
		हाल WMFW_ABSOLUTE:
			region_name = "Absolute";
			reg = offset;
			अवरोध;
		हाल WMFW_ADSP1_PM:
		हाल WMFW_ADSP1_DM:
		हाल WMFW_ADSP2_XM:
		हाल WMFW_ADSP2_YM:
		हाल WMFW_ADSP1_ZM:
		हाल WMFW_HALO_PM_PACKED:
		हाल WMFW_HALO_XM_PACKED:
		हाल WMFW_HALO_YM_PACKED:
			mem = wm_adsp_find_region(dsp, type);
			अगर (!mem) अणु
				adsp_err(dsp, "No region of type: %x\n", type);
				ret = -EINVAL;
				जाओ out_fw;
			पूर्ण

			region_name = wm_adsp_mem_region_name(type);
			reg = dsp->ops->region_to_reg(mem, offset);
			अवरोध;
		शेष:
			adsp_warn(dsp,
				  "%s.%d: Unknown region type %x at %d(%x)\n",
				  file, regions, type, pos, pos);
			अवरोध;
		पूर्ण

		adsp_dbg(dsp, "%s.%d: %d bytes at %d in %s\n", file,
			 regions, le32_to_cpu(region->len), offset,
			 region_name);

		अगर (le32_to_cpu(region->len) >
		    firmware->size - pos - माप(*region)) अणु
			adsp_err(dsp,
				 "%s.%d: %s region len %d bytes exceeds file length %zu\n",
				 file, regions, region_name,
				 le32_to_cpu(region->len), firmware->size);
			ret = -EINVAL;
			जाओ out_fw;
		पूर्ण

		अगर (text) अणु
			स_नकल(text, region->data, le32_to_cpu(region->len));
			adsp_info(dsp, "%s: %s\n", file, text);
			kमुक्त(text);
			text = शून्य;
		पूर्ण

		अगर (reg) अणु
			buf = wm_adsp_buf_alloc(region->data,
						le32_to_cpu(region->len),
						&buf_list);
			अगर (!buf) अणु
				adsp_err(dsp, "Out of memory\n");
				ret = -ENOMEM;
				जाओ out_fw;
			पूर्ण

			ret = regmap_raw_ग_लिखो_async(regmap, reg, buf->buf,
						     le32_to_cpu(region->len));
			अगर (ret != 0) अणु
				adsp_err(dsp,
					"%s.%d: Failed to write %d bytes at %d in %s: %d\n",
					file, regions,
					le32_to_cpu(region->len), offset,
					region_name, ret);
				जाओ out_fw;
			पूर्ण
		पूर्ण

		pos += le32_to_cpu(region->len) + माप(*region);
		regions++;
	पूर्ण

	ret = regmap_async_complete(regmap);
	अगर (ret != 0) अणु
		adsp_err(dsp, "Failed to complete async write: %d\n", ret);
		जाओ out_fw;
	पूर्ण

	अगर (pos > firmware->size)
		adsp_warn(dsp, "%s.%d: %zu bytes at end of file\n",
			  file, regions, pos - firmware->size);

	wm_adsp_debugfs_save_wmfwname(dsp, file);

out_fw:
	regmap_async_complete(regmap);
	wm_adsp_buf_मुक्त(&buf_list);
	release_firmware(firmware);
	kमुक्त(text);
out:
	kमुक्त(file);

	वापस ret;
पूर्ण

/*
 * Find wm_coeff_ctl with input name as its subname
 * If not found, वापस शून्य
 */
अटल काष्ठा wm_coeff_ctl *wm_adsp_get_ctl(काष्ठा wm_adsp *dsp,
					     स्थिर अक्षर *name, पूर्णांक type,
					     अचिन्हित पूर्णांक alg)
अणु
	काष्ठा wm_coeff_ctl *pos, *rslt = शून्य;
	स्थिर अक्षर *fw_txt = wm_adsp_fw_text[dsp->fw];

	list_क्रम_each_entry(pos, &dsp->ctl_list, list) अणु
		अगर (!pos->subname)
			जारी;
		अगर (म_भेदन(pos->subname, name, pos->subname_len) == 0 &&
		    म_भेदन(pos->fw_name, fw_txt,
			    SNDRV_CTL_ELEM_ID_NAME_MAXLEN) == 0 &&
				pos->alg_region.alg == alg &&
				pos->alg_region.type == type) अणु
			rslt = pos;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rslt;
पूर्ण

पूर्णांक wm_adsp_ग_लिखो_ctl(काष्ठा wm_adsp *dsp, स्थिर अक्षर *name, पूर्णांक type,
		      अचिन्हित पूर्णांक alg, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wm_coeff_ctl *ctl;
	काष्ठा snd_kcontrol *kcontrol;
	अक्षर ctl_name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	पूर्णांक ret;

	ctl = wm_adsp_get_ctl(dsp, name, type, alg);
	अगर (!ctl)
		वापस -EINVAL;

	अगर (len > ctl->len)
		वापस -EINVAL;

	ret = wm_coeff_ग_लिखो_ctrl(ctl, buf, len);
	अगर (ret)
		वापस ret;

	अगर (ctl->flags & WMFW_CTL_FLAG_SYS)
		वापस 0;

	अगर (dsp->component->name_prefix)
		snम_लिखो(ctl_name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN, "%s %s",
			 dsp->component->name_prefix, ctl->name);
	अन्यथा
		snम_लिखो(ctl_name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN, "%s",
			 ctl->name);

	kcontrol = snd_soc_card_get_kcontrol(dsp->component->card, ctl_name);
	अगर (!kcontrol) अणु
		adsp_err(dsp, "Can't find kcontrol %s\n", ctl_name);
		वापस -EINVAL;
	पूर्ण

	snd_ctl_notअगरy(dsp->component->card->snd_card,
		       SNDRV_CTL_EVENT_MASK_VALUE, &kcontrol->id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_ग_लिखो_ctl);

पूर्णांक wm_adsp_पढ़ो_ctl(काष्ठा wm_adsp *dsp, स्थिर अक्षर *name, पूर्णांक type,
		     अचिन्हित पूर्णांक alg, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wm_coeff_ctl *ctl;

	ctl = wm_adsp_get_ctl(dsp, name, type, alg);
	अगर (!ctl)
		वापस -EINVAL;

	अगर (len > ctl->len)
		वापस -EINVAL;

	वापस wm_coeff_पढ़ो_ctrl(ctl, buf, len);
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_पढ़ो_ctl);

अटल व्योम wm_adsp_ctl_fixup_base(काष्ठा wm_adsp *dsp,
				  स्थिर काष्ठा wm_adsp_alg_region *alg_region)
अणु
	काष्ठा wm_coeff_ctl *ctl;

	list_क्रम_each_entry(ctl, &dsp->ctl_list, list) अणु
		अगर (ctl->fw_name == wm_adsp_fw_text[dsp->fw] &&
		    alg_region->alg == ctl->alg_region.alg &&
		    alg_region->type == ctl->alg_region.type) अणु
			ctl->alg_region.base = alg_region->base;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम *wm_adsp_पढ़ो_algs(काष्ठा wm_adsp *dsp, माप_प्रकार n_algs,
			       स्थिर काष्ठा wm_adsp_region *mem,
			       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक len)
अणु
	व्योम *alg;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	__be32 val;

	अगर (n_algs == 0) अणु
		adsp_err(dsp, "No algorithms\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (n_algs > 1024) अणु
		adsp_err(dsp, "Algorithm count %zx excessive\n", n_algs);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Read the terminator first to validate the length */
	reg = dsp->ops->region_to_reg(mem, pos + len);

	ret = regmap_raw_पढ़ो(dsp->regmap, reg, &val, माप(val));
	अगर (ret != 0) अणु
		adsp_err(dsp, "Failed to read algorithm list end: %d\n",
			ret);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (be32_to_cpu(val) != 0xbedead)
		adsp_warn(dsp, "Algorithm list end %x 0x%x != 0xbedead\n",
			  reg, be32_to_cpu(val));

	/* Convert length from DSP words to bytes */
	len *= माप(u32);

	alg = kzalloc(len, GFP_KERNEL | GFP_DMA);
	अगर (!alg)
		वापस ERR_PTR(-ENOMEM);

	reg = dsp->ops->region_to_reg(mem, pos);

	ret = regmap_raw_पढ़ो(dsp->regmap, reg, alg, len);
	अगर (ret != 0) अणु
		adsp_err(dsp, "Failed to read algorithm list: %d\n", ret);
		kमुक्त(alg);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस alg;
पूर्ण

अटल काष्ठा wm_adsp_alg_region *
	wm_adsp_find_alg_region(काष्ठा wm_adsp *dsp, पूर्णांक type, अचिन्हित पूर्णांक id)
अणु
	काष्ठा wm_adsp_alg_region *alg_region;

	list_क्रम_each_entry(alg_region, &dsp->alg_regions, list) अणु
		अगर (id == alg_region->alg && type == alg_region->type)
			वापस alg_region;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा wm_adsp_alg_region *wm_adsp_create_region(काष्ठा wm_adsp *dsp,
							पूर्णांक type, __be32 id,
							__be32 base)
अणु
	काष्ठा wm_adsp_alg_region *alg_region;

	alg_region = kzalloc(माप(*alg_region), GFP_KERNEL);
	अगर (!alg_region)
		वापस ERR_PTR(-ENOMEM);

	alg_region->type = type;
	alg_region->alg = be32_to_cpu(id);
	alg_region->base = be32_to_cpu(base);

	list_add_tail(&alg_region->list, &dsp->alg_regions);

	अगर (dsp->fw_ver > 0)
		wm_adsp_ctl_fixup_base(dsp, alg_region);

	वापस alg_region;
पूर्ण

अटल व्योम wm_adsp_मुक्त_alg_regions(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_adsp_alg_region *alg_region;

	जबतक (!list_empty(&dsp->alg_regions)) अणु
		alg_region = list_first_entry(&dsp->alg_regions,
					      काष्ठा wm_adsp_alg_region,
					      list);
		list_del(&alg_region->list);
		kमुक्त(alg_region);
	पूर्ण
पूर्ण

अटल व्योम wmfw_parse_id_header(काष्ठा wm_adsp *dsp,
				 काष्ठा wmfw_id_hdr *fw, पूर्णांक nalgs)
अणु
	dsp->fw_id = be32_to_cpu(fw->id);
	dsp->fw_id_version = be32_to_cpu(fw->ver);

	adsp_info(dsp, "Firmware: %x v%d.%d.%d, %d algorithms\n",
		  dsp->fw_id, (dsp->fw_id_version & 0xff0000) >> 16,
		  (dsp->fw_id_version & 0xff00) >> 8, dsp->fw_id_version & 0xff,
		  nalgs);
पूर्ण

अटल व्योम wmfw_v3_parse_id_header(काष्ठा wm_adsp *dsp,
				    काष्ठा wmfw_v3_id_hdr *fw, पूर्णांक nalgs)
अणु
	dsp->fw_id = be32_to_cpu(fw->id);
	dsp->fw_id_version = be32_to_cpu(fw->ver);
	dsp->fw_venकरोr_id = be32_to_cpu(fw->venकरोr_id);

	adsp_info(dsp, "Firmware: %x vendor: 0x%x v%d.%d.%d, %d algorithms\n",
		  dsp->fw_id, dsp->fw_venकरोr_id,
		  (dsp->fw_id_version & 0xff0000) >> 16,
		  (dsp->fw_id_version & 0xff00) >> 8, dsp->fw_id_version & 0xff,
		  nalgs);
पूर्ण

अटल पूर्णांक wm_adsp_create_regions(काष्ठा wm_adsp *dsp, __be32 id, पूर्णांक nregions,
				पूर्णांक *type, __be32 *base)
अणु
	काष्ठा wm_adsp_alg_region *alg_region;
	पूर्णांक i;

	क्रम (i = 0; i < nregions; i++) अणु
		alg_region = wm_adsp_create_region(dsp, type[i], id, base[i]);
		अगर (IS_ERR(alg_region))
			वापस PTR_ERR(alg_region);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm_adsp1_setup_algs(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wmfw_adsp1_id_hdr adsp1_id;
	काष्ठा wmfw_adsp1_alg_hdr *adsp1_alg;
	काष्ठा wm_adsp_alg_region *alg_region;
	स्थिर काष्ठा wm_adsp_region *mem;
	अचिन्हित पूर्णांक pos, len;
	माप_प्रकार n_algs;
	पूर्णांक i, ret;

	mem = wm_adsp_find_region(dsp, WMFW_ADSP1_DM);
	अगर (WARN_ON(!mem))
		वापस -EINVAL;

	ret = regmap_raw_पढ़ो(dsp->regmap, mem->base, &adsp1_id,
			      माप(adsp1_id));
	अगर (ret != 0) अणु
		adsp_err(dsp, "Failed to read algorithm info: %d\n",
			 ret);
		वापस ret;
	पूर्ण

	n_algs = be32_to_cpu(adsp1_id.n_algs);

	wmfw_parse_id_header(dsp, &adsp1_id.fw, n_algs);

	alg_region = wm_adsp_create_region(dsp, WMFW_ADSP1_ZM,
					   adsp1_id.fw.id, adsp1_id.zm);
	अगर (IS_ERR(alg_region))
		वापस PTR_ERR(alg_region);

	alg_region = wm_adsp_create_region(dsp, WMFW_ADSP1_DM,
					   adsp1_id.fw.id, adsp1_id.dm);
	अगर (IS_ERR(alg_region))
		वापस PTR_ERR(alg_region);

	/* Calculate offset and length in DSP words */
	pos = माप(adsp1_id) / माप(u32);
	len = (माप(*adsp1_alg) * n_algs) / माप(u32);

	adsp1_alg = wm_adsp_पढ़ो_algs(dsp, n_algs, mem, pos, len);
	अगर (IS_ERR(adsp1_alg))
		वापस PTR_ERR(adsp1_alg);

	क्रम (i = 0; i < n_algs; i++) अणु
		adsp_info(dsp, "%d: ID %x v%d.%d.%d DM@%x ZM@%x\n",
			  i, be32_to_cpu(adsp1_alg[i].alg.id),
			  (be32_to_cpu(adsp1_alg[i].alg.ver) & 0xff0000) >> 16,
			  (be32_to_cpu(adsp1_alg[i].alg.ver) & 0xff00) >> 8,
			  be32_to_cpu(adsp1_alg[i].alg.ver) & 0xff,
			  be32_to_cpu(adsp1_alg[i].dm),
			  be32_to_cpu(adsp1_alg[i].zm));

		alg_region = wm_adsp_create_region(dsp, WMFW_ADSP1_DM,
						   adsp1_alg[i].alg.id,
						   adsp1_alg[i].dm);
		अगर (IS_ERR(alg_region)) अणु
			ret = PTR_ERR(alg_region);
			जाओ out;
		पूर्ण
		अगर (dsp->fw_ver == 0) अणु
			अगर (i + 1 < n_algs) अणु
				len = be32_to_cpu(adsp1_alg[i + 1].dm);
				len -= be32_to_cpu(adsp1_alg[i].dm);
				len *= 4;
				wm_adsp_create_control(dsp, alg_region, 0,
						     len, शून्य, 0, 0,
						     SNDRV_CTL_ELEM_TYPE_BYTES);
			पूर्ण अन्यथा अणु
				adsp_warn(dsp, "Missing length info for region DM with ID %x\n",
					  be32_to_cpu(adsp1_alg[i].alg.id));
			पूर्ण
		पूर्ण

		alg_region = wm_adsp_create_region(dsp, WMFW_ADSP1_ZM,
						   adsp1_alg[i].alg.id,
						   adsp1_alg[i].zm);
		अगर (IS_ERR(alg_region)) अणु
			ret = PTR_ERR(alg_region);
			जाओ out;
		पूर्ण
		अगर (dsp->fw_ver == 0) अणु
			अगर (i + 1 < n_algs) अणु
				len = be32_to_cpu(adsp1_alg[i + 1].zm);
				len -= be32_to_cpu(adsp1_alg[i].zm);
				len *= 4;
				wm_adsp_create_control(dsp, alg_region, 0,
						     len, शून्य, 0, 0,
						     SNDRV_CTL_ELEM_TYPE_BYTES);
			पूर्ण अन्यथा अणु
				adsp_warn(dsp, "Missing length info for region ZM with ID %x\n",
					  be32_to_cpu(adsp1_alg[i].alg.id));
			पूर्ण
		पूर्ण
	पूर्ण

out:
	kमुक्त(adsp1_alg);
	वापस ret;
पूर्ण

अटल पूर्णांक wm_adsp2_setup_algs(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wmfw_adsp2_id_hdr adsp2_id;
	काष्ठा wmfw_adsp2_alg_hdr *adsp2_alg;
	काष्ठा wm_adsp_alg_region *alg_region;
	स्थिर काष्ठा wm_adsp_region *mem;
	अचिन्हित पूर्णांक pos, len;
	माप_प्रकार n_algs;
	पूर्णांक i, ret;

	mem = wm_adsp_find_region(dsp, WMFW_ADSP2_XM);
	अगर (WARN_ON(!mem))
		वापस -EINVAL;

	ret = regmap_raw_पढ़ो(dsp->regmap, mem->base, &adsp2_id,
			      माप(adsp2_id));
	अगर (ret != 0) अणु
		adsp_err(dsp, "Failed to read algorithm info: %d\n",
			 ret);
		वापस ret;
	पूर्ण

	n_algs = be32_to_cpu(adsp2_id.n_algs);

	wmfw_parse_id_header(dsp, &adsp2_id.fw, n_algs);

	alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_XM,
					   adsp2_id.fw.id, adsp2_id.xm);
	अगर (IS_ERR(alg_region))
		वापस PTR_ERR(alg_region);

	alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_YM,
					   adsp2_id.fw.id, adsp2_id.ym);
	अगर (IS_ERR(alg_region))
		वापस PTR_ERR(alg_region);

	alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_ZM,
					   adsp2_id.fw.id, adsp2_id.zm);
	अगर (IS_ERR(alg_region))
		वापस PTR_ERR(alg_region);

	/* Calculate offset and length in DSP words */
	pos = माप(adsp2_id) / माप(u32);
	len = (माप(*adsp2_alg) * n_algs) / माप(u32);

	adsp2_alg = wm_adsp_पढ़ो_algs(dsp, n_algs, mem, pos, len);
	अगर (IS_ERR(adsp2_alg))
		वापस PTR_ERR(adsp2_alg);

	क्रम (i = 0; i < n_algs; i++) अणु
		adsp_info(dsp,
			  "%d: ID %x v%d.%d.%d XM@%x YM@%x ZM@%x\n",
			  i, be32_to_cpu(adsp2_alg[i].alg.id),
			  (be32_to_cpu(adsp2_alg[i].alg.ver) & 0xff0000) >> 16,
			  (be32_to_cpu(adsp2_alg[i].alg.ver) & 0xff00) >> 8,
			  be32_to_cpu(adsp2_alg[i].alg.ver) & 0xff,
			  be32_to_cpu(adsp2_alg[i].xm),
			  be32_to_cpu(adsp2_alg[i].ym),
			  be32_to_cpu(adsp2_alg[i].zm));

		alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_XM,
						   adsp2_alg[i].alg.id,
						   adsp2_alg[i].xm);
		अगर (IS_ERR(alg_region)) अणु
			ret = PTR_ERR(alg_region);
			जाओ out;
		पूर्ण
		अगर (dsp->fw_ver == 0) अणु
			अगर (i + 1 < n_algs) अणु
				len = be32_to_cpu(adsp2_alg[i + 1].xm);
				len -= be32_to_cpu(adsp2_alg[i].xm);
				len *= 4;
				wm_adsp_create_control(dsp, alg_region, 0,
						     len, शून्य, 0, 0,
						     SNDRV_CTL_ELEM_TYPE_BYTES);
			पूर्ण अन्यथा अणु
				adsp_warn(dsp, "Missing length info for region XM with ID %x\n",
					  be32_to_cpu(adsp2_alg[i].alg.id));
			पूर्ण
		पूर्ण

		alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_YM,
						   adsp2_alg[i].alg.id,
						   adsp2_alg[i].ym);
		अगर (IS_ERR(alg_region)) अणु
			ret = PTR_ERR(alg_region);
			जाओ out;
		पूर्ण
		अगर (dsp->fw_ver == 0) अणु
			अगर (i + 1 < n_algs) अणु
				len = be32_to_cpu(adsp2_alg[i + 1].ym);
				len -= be32_to_cpu(adsp2_alg[i].ym);
				len *= 4;
				wm_adsp_create_control(dsp, alg_region, 0,
						     len, शून्य, 0, 0,
						     SNDRV_CTL_ELEM_TYPE_BYTES);
			पूर्ण अन्यथा अणु
				adsp_warn(dsp, "Missing length info for region YM with ID %x\n",
					  be32_to_cpu(adsp2_alg[i].alg.id));
			पूर्ण
		पूर्ण

		alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_ZM,
						   adsp2_alg[i].alg.id,
						   adsp2_alg[i].zm);
		अगर (IS_ERR(alg_region)) अणु
			ret = PTR_ERR(alg_region);
			जाओ out;
		पूर्ण
		अगर (dsp->fw_ver == 0) अणु
			अगर (i + 1 < n_algs) अणु
				len = be32_to_cpu(adsp2_alg[i + 1].zm);
				len -= be32_to_cpu(adsp2_alg[i].zm);
				len *= 4;
				wm_adsp_create_control(dsp, alg_region, 0,
						     len, शून्य, 0, 0,
						     SNDRV_CTL_ELEM_TYPE_BYTES);
			पूर्ण अन्यथा अणु
				adsp_warn(dsp, "Missing length info for region ZM with ID %x\n",
					  be32_to_cpu(adsp2_alg[i].alg.id));
			पूर्ण
		पूर्ण
	पूर्ण

out:
	kमुक्त(adsp2_alg);
	वापस ret;
पूर्ण

अटल पूर्णांक wm_halo_create_regions(काष्ठा wm_adsp *dsp, __be32 id,
				  __be32 xm_base, __be32 ym_base)
अणु
	पूर्णांक types[] = अणु
		WMFW_ADSP2_XM, WMFW_HALO_XM_PACKED,
		WMFW_ADSP2_YM, WMFW_HALO_YM_PACKED
	पूर्ण;
	__be32 bases[] = अणु xm_base, xm_base, ym_base, ym_base पूर्ण;

	वापस wm_adsp_create_regions(dsp, id, ARRAY_SIZE(types), types, bases);
पूर्ण

अटल पूर्णांक wm_halo_setup_algs(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wmfw_halo_id_hdr halo_id;
	काष्ठा wmfw_halo_alg_hdr *halo_alg;
	स्थिर काष्ठा wm_adsp_region *mem;
	अचिन्हित पूर्णांक pos, len;
	माप_प्रकार n_algs;
	पूर्णांक i, ret;

	mem = wm_adsp_find_region(dsp, WMFW_ADSP2_XM);
	अगर (WARN_ON(!mem))
		वापस -EINVAL;

	ret = regmap_raw_पढ़ो(dsp->regmap, mem->base, &halo_id,
			      माप(halo_id));
	अगर (ret != 0) अणु
		adsp_err(dsp, "Failed to read algorithm info: %d\n",
			 ret);
		वापस ret;
	पूर्ण

	n_algs = be32_to_cpu(halo_id.n_algs);

	wmfw_v3_parse_id_header(dsp, &halo_id.fw, n_algs);

	ret = wm_halo_create_regions(dsp, halo_id.fw.id,
				     halo_id.xm_base, halo_id.ym_base);
	अगर (ret)
		वापस ret;

	/* Calculate offset and length in DSP words */
	pos = माप(halo_id) / माप(u32);
	len = (माप(*halo_alg) * n_algs) / माप(u32);

	halo_alg = wm_adsp_पढ़ो_algs(dsp, n_algs, mem, pos, len);
	अगर (IS_ERR(halo_alg))
		वापस PTR_ERR(halo_alg);

	क्रम (i = 0; i < n_algs; i++) अणु
		adsp_info(dsp,
			  "%d: ID %x v%d.%d.%d XM@%x YM@%x\n",
			  i, be32_to_cpu(halo_alg[i].alg.id),
			  (be32_to_cpu(halo_alg[i].alg.ver) & 0xff0000) >> 16,
			  (be32_to_cpu(halo_alg[i].alg.ver) & 0xff00) >> 8,
			  be32_to_cpu(halo_alg[i].alg.ver) & 0xff,
			  be32_to_cpu(halo_alg[i].xm_base),
			  be32_to_cpu(halo_alg[i].ym_base));

		ret = wm_halo_create_regions(dsp, halo_alg[i].alg.id,
					     halo_alg[i].xm_base,
					     halo_alg[i].ym_base);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	kमुक्त(halo_alg);
	वापस ret;
पूर्ण

अटल पूर्णांक wm_adsp_load_coeff(काष्ठा wm_adsp *dsp)
अणु
	LIST_HEAD(buf_list);
	काष्ठा regmap *regmap = dsp->regmap;
	काष्ठा wmfw_coeff_hdr *hdr;
	काष्ठा wmfw_coeff_item *blk;
	स्थिर काष्ठा firmware *firmware;
	स्थिर काष्ठा wm_adsp_region *mem;
	काष्ठा wm_adsp_alg_region *alg_region;
	स्थिर अक्षर *region_name;
	पूर्णांक ret, pos, blocks, type, offset, reg;
	अक्षर *file;
	काष्ठा wm_adsp_buf *buf;

	file = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (file == शून्य)
		वापस -ENOMEM;

	snम_लिखो(file, PAGE_SIZE, "%s-%s-%s.bin", dsp->part, dsp->fwf_name,
		 wm_adsp_fw[dsp->fw].file);
	file[PAGE_SIZE - 1] = '\0';

	ret = request_firmware(&firmware, file, dsp->dev);
	अगर (ret != 0) अणु
		adsp_warn(dsp, "Failed to request '%s'\n", file);
		ret = 0;
		जाओ out;
	पूर्ण
	ret = -EINVAL;

	अगर (माप(*hdr) >= firmware->size) अणु
		adsp_err(dsp, "%s: file too short, %zu bytes\n",
			file, firmware->size);
		जाओ out_fw;
	पूर्ण

	hdr = (व्योम *)&firmware->data[0];
	अगर (स_भेद(hdr->magic, "WMDR", 4) != 0) अणु
		adsp_err(dsp, "%s: invalid magic\n", file);
		जाओ out_fw;
	पूर्ण

	चयन (be32_to_cpu(hdr->rev) & 0xff) अणु
	हाल 1:
		अवरोध;
	शेष:
		adsp_err(dsp, "%s: Unsupported coefficient file format %d\n",
			 file, be32_to_cpu(hdr->rev) & 0xff);
		ret = -EINVAL;
		जाओ out_fw;
	पूर्ण

	adsp_dbg(dsp, "%s: v%d.%d.%d\n", file,
		(le32_to_cpu(hdr->ver) >> 16) & 0xff,
		(le32_to_cpu(hdr->ver) >>  8) & 0xff,
		le32_to_cpu(hdr->ver) & 0xff);

	pos = le32_to_cpu(hdr->len);

	blocks = 0;
	जबतक (pos < firmware->size &&
	       माप(*blk) < firmware->size - pos) अणु
		blk = (व्योम *)(&firmware->data[pos]);

		type = le16_to_cpu(blk->type);
		offset = le16_to_cpu(blk->offset);

		adsp_dbg(dsp, "%s.%d: %x v%d.%d.%d\n",
			 file, blocks, le32_to_cpu(blk->id),
			 (le32_to_cpu(blk->ver) >> 16) & 0xff,
			 (le32_to_cpu(blk->ver) >>  8) & 0xff,
			 le32_to_cpu(blk->ver) & 0xff);
		adsp_dbg(dsp, "%s.%d: %d bytes at 0x%x in %x\n",
			 file, blocks, le32_to_cpu(blk->len), offset, type);

		reg = 0;
		region_name = "Unknown";
		चयन (type) अणु
		हाल (WMFW_NAME_TEXT << 8):
		हाल (WMFW_INFO_TEXT << 8):
		हाल (WMFW_METADATA << 8):
			अवरोध;
		हाल (WMFW_ABSOLUTE << 8):
			/*
			 * Old files may use this क्रम global
			 * coefficients.
			 */
			अगर (le32_to_cpu(blk->id) == dsp->fw_id &&
			    offset == 0) अणु
				region_name = "global coefficients";
				mem = wm_adsp_find_region(dsp, type);
				अगर (!mem) अणु
					adsp_err(dsp, "No ZM\n");
					अवरोध;
				पूर्ण
				reg = dsp->ops->region_to_reg(mem, 0);

			पूर्ण अन्यथा अणु
				region_name = "register";
				reg = offset;
			पूर्ण
			अवरोध;

		हाल WMFW_ADSP1_DM:
		हाल WMFW_ADSP1_ZM:
		हाल WMFW_ADSP2_XM:
		हाल WMFW_ADSP2_YM:
		हाल WMFW_HALO_XM_PACKED:
		हाल WMFW_HALO_YM_PACKED:
		हाल WMFW_HALO_PM_PACKED:
			adsp_dbg(dsp, "%s.%d: %d bytes in %x for %x\n",
				 file, blocks, le32_to_cpu(blk->len),
				 type, le32_to_cpu(blk->id));

			mem = wm_adsp_find_region(dsp, type);
			अगर (!mem) अणु
				adsp_err(dsp, "No base for region %x\n", type);
				अवरोध;
			पूर्ण

			alg_region = wm_adsp_find_alg_region(dsp, type,
						le32_to_cpu(blk->id));
			अगर (alg_region) अणु
				reg = alg_region->base;
				reg = dsp->ops->region_to_reg(mem, reg);
				reg += offset;
			पूर्ण अन्यथा अणु
				adsp_err(dsp, "No %x for algorithm %x\n",
					 type, le32_to_cpu(blk->id));
			पूर्ण
			अवरोध;

		शेष:
			adsp_err(dsp, "%s.%d: Unknown region type %x at %d\n",
				 file, blocks, type, pos);
			अवरोध;
		पूर्ण

		अगर (reg) अणु
			अगर (le32_to_cpu(blk->len) >
			    firmware->size - pos - माप(*blk)) अणु
				adsp_err(dsp,
					 "%s.%d: %s region len %d bytes exceeds file length %zu\n",
					 file, blocks, region_name,
					 le32_to_cpu(blk->len),
					 firmware->size);
				ret = -EINVAL;
				जाओ out_fw;
			पूर्ण

			buf = wm_adsp_buf_alloc(blk->data,
						le32_to_cpu(blk->len),
						&buf_list);
			अगर (!buf) अणु
				adsp_err(dsp, "Out of memory\n");
				ret = -ENOMEM;
				जाओ out_fw;
			पूर्ण

			adsp_dbg(dsp, "%s.%d: Writing %d bytes at %x\n",
				 file, blocks, le32_to_cpu(blk->len),
				 reg);
			ret = regmap_raw_ग_लिखो_async(regmap, reg, buf->buf,
						     le32_to_cpu(blk->len));
			अगर (ret != 0) अणु
				adsp_err(dsp,
					"%s.%d: Failed to write to %x in %s: %d\n",
					file, blocks, reg, region_name, ret);
			पूर्ण
		पूर्ण

		pos += (le32_to_cpu(blk->len) + माप(*blk) + 3) & ~0x03;
		blocks++;
	पूर्ण

	ret = regmap_async_complete(regmap);
	अगर (ret != 0)
		adsp_err(dsp, "Failed to complete async write: %d\n", ret);

	अगर (pos > firmware->size)
		adsp_warn(dsp, "%s.%d: %zu bytes at end of file\n",
			  file, blocks, pos - firmware->size);

	wm_adsp_debugfs_save_binname(dsp, file);

out_fw:
	regmap_async_complete(regmap);
	release_firmware(firmware);
	wm_adsp_buf_मुक्त(&buf_list);
out:
	kमुक्त(file);
	वापस ret;
पूर्ण

अटल पूर्णांक wm_adsp_create_name(काष्ठा wm_adsp *dsp)
अणु
	अक्षर *p;

	अगर (!dsp->name) अणु
		dsp->name = devm_kaप्र_लिखो(dsp->dev, GFP_KERNEL, "DSP%d",
					   dsp->num);
		अगर (!dsp->name)
			वापस -ENOMEM;
	पूर्ण

	अगर (!dsp->fwf_name) अणु
		p = devm_kstrdup(dsp->dev, dsp->name, GFP_KERNEL);
		अगर (!p)
			वापस -ENOMEM;

		dsp->fwf_name = p;
		क्रम (; *p != 0; ++p)
			*p = छोटे(*p);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm_adsp_common_init(काष्ठा wm_adsp *dsp)
अणु
	पूर्णांक ret;

	ret = wm_adsp_create_name(dsp);
	अगर (ret)
		वापस ret;

	INIT_LIST_HEAD(&dsp->alg_regions);
	INIT_LIST_HEAD(&dsp->ctl_list);
	INIT_LIST_HEAD(&dsp->compr_list);
	INIT_LIST_HEAD(&dsp->buffer_list);

	mutex_init(&dsp->pwr_lock);

	वापस 0;
पूर्ण

पूर्णांक wm_adsp1_init(काष्ठा wm_adsp *dsp)
अणु
	dsp->ops = &wm_adsp1_ops;

	वापस wm_adsp_common_init(dsp);
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp1_init);

पूर्णांक wm_adsp1_event(काष्ठा snd_soc_dapm_widget *w,
		   काष्ठा snd_kcontrol *kcontrol,
		   पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm_adsp *dsps = snd_soc_component_get_drvdata(component);
	काष्ठा wm_adsp *dsp = &dsps[w->shअगरt];
	काष्ठा wm_coeff_ctl *ctl;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	dsp->component = component;

	mutex_lock(&dsp->pwr_lock);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(dsp->regmap, dsp->base + ADSP1_CONTROL_30,
				   ADSP1_SYS_ENA, ADSP1_SYS_ENA);

		/*
		 * For simplicity set the DSP घड़ी rate to be the
		 * SYSCLK rate rather than making it configurable.
		 */
		अगर (dsp->sysclk_reg) अणु
			ret = regmap_पढ़ो(dsp->regmap, dsp->sysclk_reg, &val);
			अगर (ret != 0) अणु
				adsp_err(dsp, "Failed to read SYSCLK state: %d\n",
				ret);
				जाओ err_mutex;
			पूर्ण

			val = (val & dsp->sysclk_mask) >> dsp->sysclk_shअगरt;

			ret = regmap_update_bits(dsp->regmap,
						 dsp->base + ADSP1_CONTROL_31,
						 ADSP1_CLK_SEL_MASK, val);
			अगर (ret != 0) अणु
				adsp_err(dsp, "Failed to set clock rate: %d\n",
					 ret);
				जाओ err_mutex;
			पूर्ण
		पूर्ण

		ret = wm_adsp_load(dsp);
		अगर (ret != 0)
			जाओ err_ena;

		ret = wm_adsp1_setup_algs(dsp);
		अगर (ret != 0)
			जाओ err_ena;

		ret = wm_adsp_load_coeff(dsp);
		अगर (ret != 0)
			जाओ err_ena;

		/* Initialize caches क्रम enabled and unset controls */
		ret = wm_coeff_init_control_caches(dsp);
		अगर (ret != 0)
			जाओ err_ena;

		/* Sync set controls */
		ret = wm_coeff_sync_controls(dsp);
		अगर (ret != 0)
			जाओ err_ena;

		dsp->booted = true;

		/* Start the core running */
		regmap_update_bits(dsp->regmap, dsp->base + ADSP1_CONTROL_30,
				   ADSP1_CORE_ENA | ADSP1_START,
				   ADSP1_CORE_ENA | ADSP1_START);

		dsp->running = true;
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		dsp->running = false;
		dsp->booted = false;

		/* Halt the core */
		regmap_update_bits(dsp->regmap, dsp->base + ADSP1_CONTROL_30,
				   ADSP1_CORE_ENA | ADSP1_START, 0);

		regmap_update_bits(dsp->regmap, dsp->base + ADSP1_CONTROL_19,
				   ADSP1_WDMA_BUFFER_LENGTH_MASK, 0);

		regmap_update_bits(dsp->regmap, dsp->base + ADSP1_CONTROL_30,
				   ADSP1_SYS_ENA, 0);

		list_क्रम_each_entry(ctl, &dsp->ctl_list, list)
			ctl->enabled = 0;


		wm_adsp_मुक्त_alg_regions(dsp);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&dsp->pwr_lock);

	वापस 0;

err_ena:
	regmap_update_bits(dsp->regmap, dsp->base + ADSP1_CONTROL_30,
			   ADSP1_SYS_ENA, 0);
err_mutex:
	mutex_unlock(&dsp->pwr_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp1_event);

अटल पूर्णांक wm_adsp2v2_enable_core(काष्ठा wm_adsp *dsp)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, count;

	/* Wait क्रम the RAM to start, should be near instantaneous */
	क्रम (count = 0; count < 10; ++count) अणु
		ret = regmap_पढ़ो(dsp->regmap, dsp->base + ADSP2_STATUS1, &val);
		अगर (ret != 0)
			वापस ret;

		अगर (val & ADSP2_RAM_RDY)
			अवरोध;

		usleep_range(250, 500);
	पूर्ण

	अगर (!(val & ADSP2_RAM_RDY)) अणु
		adsp_err(dsp, "Failed to start DSP RAM\n");
		वापस -EBUSY;
	पूर्ण

	adsp_dbg(dsp, "RAM ready after %d polls\n", count);

	वापस 0;
पूर्ण

अटल पूर्णांक wm_adsp2_enable_core(काष्ठा wm_adsp *dsp)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits_async(dsp->regmap, dsp->base + ADSP2_CONTROL,
				       ADSP2_SYS_ENA, ADSP2_SYS_ENA);
	अगर (ret != 0)
		वापस ret;

	वापस wm_adsp2v2_enable_core(dsp);
पूर्ण

अटल पूर्णांक wm_adsp2_lock(काष्ठा wm_adsp *dsp, अचिन्हित पूर्णांक lock_regions)
अणु
	काष्ठा regmap *regmap = dsp->regmap;
	अचिन्हित पूर्णांक code0, code1, lock_reg;

	अगर (!(lock_regions & WM_ADSP2_REGION_ALL))
		वापस 0;

	lock_regions &= WM_ADSP2_REGION_ALL;
	lock_reg = dsp->base + ADSP2_LOCK_REGION_1_LOCK_REGION_0;

	जबतक (lock_regions) अणु
		code0 = code1 = 0;
		अगर (lock_regions & BIT(0)) अणु
			code0 = ADSP2_LOCK_CODE_0;
			code1 = ADSP2_LOCK_CODE_1;
		पूर्ण
		अगर (lock_regions & BIT(1)) अणु
			code0 |= ADSP2_LOCK_CODE_0 << ADSP2_LOCK_REGION_SHIFT;
			code1 |= ADSP2_LOCK_CODE_1 << ADSP2_LOCK_REGION_SHIFT;
		पूर्ण
		regmap_ग_लिखो(regmap, lock_reg, code0);
		regmap_ग_लिखो(regmap, lock_reg, code1);
		lock_regions >>= 2;
		lock_reg += 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm_adsp2_enable_memory(काष्ठा wm_adsp *dsp)
अणु
	वापस regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
				  ADSP2_MEM_ENA, ADSP2_MEM_ENA);
पूर्ण

अटल व्योम wm_adsp2_disable_memory(काष्ठा wm_adsp *dsp)
अणु
	regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
			   ADSP2_MEM_ENA, 0);
पूर्ण

अटल व्योम wm_adsp2_disable_core(काष्ठा wm_adsp *dsp)
अणु
	regmap_ग_लिखो(dsp->regmap, dsp->base + ADSP2_RDMA_CONFIG_1, 0);
	regmap_ग_लिखो(dsp->regmap, dsp->base + ADSP2_WDMA_CONFIG_1, 0);
	regmap_ग_लिखो(dsp->regmap, dsp->base + ADSP2_WDMA_CONFIG_2, 0);

	regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
			   ADSP2_SYS_ENA, 0);
पूर्ण

अटल व्योम wm_adsp2v2_disable_core(काष्ठा wm_adsp *dsp)
अणु
	regmap_ग_लिखो(dsp->regmap, dsp->base + ADSP2_RDMA_CONFIG_1, 0);
	regmap_ग_लिखो(dsp->regmap, dsp->base + ADSP2_WDMA_CONFIG_1, 0);
	regmap_ग_लिखो(dsp->regmap, dsp->base + ADSP2V2_WDMA_CONFIG_2, 0);
पूर्ण

अटल व्योम wm_adsp_boot_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm_adsp *dsp = container_of(work,
					   काष्ठा wm_adsp,
					   boot_work);
	पूर्णांक ret;

	mutex_lock(&dsp->pwr_lock);

	अगर (dsp->ops->enable_memory) अणु
		ret = dsp->ops->enable_memory(dsp);
		अगर (ret != 0)
			जाओ err_mutex;
	पूर्ण

	अगर (dsp->ops->enable_core) अणु
		ret = dsp->ops->enable_core(dsp);
		अगर (ret != 0)
			जाओ err_mem;
	पूर्ण

	ret = wm_adsp_load(dsp);
	अगर (ret != 0)
		जाओ err_ena;

	ret = dsp->ops->setup_algs(dsp);
	अगर (ret != 0)
		जाओ err_ena;

	ret = wm_adsp_load_coeff(dsp);
	अगर (ret != 0)
		जाओ err_ena;

	/* Initialize caches क्रम enabled and unset controls */
	ret = wm_coeff_init_control_caches(dsp);
	अगर (ret != 0)
		जाओ err_ena;

	अगर (dsp->ops->disable_core)
		dsp->ops->disable_core(dsp);

	dsp->booted = true;

	mutex_unlock(&dsp->pwr_lock);

	वापस;

err_ena:
	अगर (dsp->ops->disable_core)
		dsp->ops->disable_core(dsp);
err_mem:
	अगर (dsp->ops->disable_memory)
		dsp->ops->disable_memory(dsp);
err_mutex:
	mutex_unlock(&dsp->pwr_lock);
पूर्ण

अटल पूर्णांक wm_halo_configure_mpu(काष्ठा wm_adsp *dsp, अचिन्हित पूर्णांक lock_regions)
अणु
	काष्ठा reg_sequence config[] = अणु
		अणु dsp->base + HALO_MPU_LOCK_CONFIG,     0x5555 पूर्ण,
		अणु dsp->base + HALO_MPU_LOCK_CONFIG,     0xAAAA पूर्ण,
		अणु dsp->base + HALO_MPU_XMEM_ACCESS_0,   0xFFFFFFFF पूर्ण,
		अणु dsp->base + HALO_MPU_YMEM_ACCESS_0,   0xFFFFFFFF पूर्ण,
		अणु dsp->base + HALO_MPU_WINDOW_ACCESS_0, lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_XREG_ACCESS_0,   lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_YREG_ACCESS_0,   lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_XMEM_ACCESS_1,   0xFFFFFFFF पूर्ण,
		अणु dsp->base + HALO_MPU_YMEM_ACCESS_1,   0xFFFFFFFF पूर्ण,
		अणु dsp->base + HALO_MPU_WINDOW_ACCESS_1, lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_XREG_ACCESS_1,   lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_YREG_ACCESS_1,   lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_XMEM_ACCESS_2,   0xFFFFFFFF पूर्ण,
		अणु dsp->base + HALO_MPU_YMEM_ACCESS_2,   0xFFFFFFFF पूर्ण,
		अणु dsp->base + HALO_MPU_WINDOW_ACCESS_2, lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_XREG_ACCESS_2,   lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_YREG_ACCESS_2,   lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_XMEM_ACCESS_3,   0xFFFFFFFF पूर्ण,
		अणु dsp->base + HALO_MPU_YMEM_ACCESS_3,   0xFFFFFFFF पूर्ण,
		अणु dsp->base + HALO_MPU_WINDOW_ACCESS_3, lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_XREG_ACCESS_3,   lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_YREG_ACCESS_3,   lock_regions पूर्ण,
		अणु dsp->base + HALO_MPU_LOCK_CONFIG,     0 पूर्ण,
	पूर्ण;

	वापस regmap_multi_reg_ग_लिखो(dsp->regmap, config, ARRAY_SIZE(config));
पूर्ण

पूर्णांक wm_adsp2_set_dspclk(काष्ठा snd_soc_dapm_widget *w, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm_adsp *dsps = snd_soc_component_get_drvdata(component);
	काष्ठा wm_adsp *dsp = &dsps[w->shअगरt];
	पूर्णांक ret;

	ret = regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CLOCKING,
				 ADSP2_CLK_SEL_MASK,
				 freq << ADSP2_CLK_SEL_SHIFT);
	अगर (ret)
		adsp_err(dsp, "Failed to set clock rate: %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp2_set_dspclk);

पूर्णांक wm_adsp2_preloader_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm_adsp *dsps = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा wm_adsp *dsp = &dsps[mc->shअगरt - 1];

	ucontrol->value.पूर्णांकeger.value[0] = dsp->preloaded;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp2_preloader_get);

पूर्णांक wm_adsp2_preloader_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm_adsp *dsps = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा wm_adsp *dsp = &dsps[mc->shअगरt - 1];
	अक्षर preload[32];

	snम_लिखो(preload, ARRAY_SIZE(preload), "%s Preload", dsp->name);

	dsp->preloaded = ucontrol->value.पूर्णांकeger.value[0];

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		snd_soc_component_क्रमce_enable_pin(component, preload);
	अन्यथा
		snd_soc_component_disable_pin(component, preload);

	snd_soc_dapm_sync(dapm);

	flush_work(&dsp->boot_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp2_preloader_put);

अटल व्योम wm_adsp_stop_watchकरोg(काष्ठा wm_adsp *dsp)
अणु
	regmap_update_bits(dsp->regmap, dsp->base + ADSP2_WATCHDOG,
			   ADSP2_WDT_ENA_MASK, 0);
पूर्ण

अटल व्योम wm_halo_stop_watchकरोg(काष्ठा wm_adsp *dsp)
अणु
	regmap_update_bits(dsp->regmap, dsp->base + HALO_WDT_CONTROL,
			   HALO_WDT_EN_MASK, 0);
पूर्ण

पूर्णांक wm_adsp_early_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm_adsp *dsps = snd_soc_component_get_drvdata(component);
	काष्ठा wm_adsp *dsp = &dsps[w->shअगरt];
	काष्ठा wm_coeff_ctl *ctl;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		queue_work(प्रणाली_unbound_wq, &dsp->boot_work);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		mutex_lock(&dsp->pwr_lock);

		wm_adsp_debugfs_clear(dsp);

		dsp->fw_id = 0;
		dsp->fw_id_version = 0;

		dsp->booted = false;

		अगर (dsp->ops->disable_memory)
			dsp->ops->disable_memory(dsp);

		list_क्रम_each_entry(ctl, &dsp->ctl_list, list)
			ctl->enabled = 0;

		wm_adsp_मुक्त_alg_regions(dsp);

		mutex_unlock(&dsp->pwr_lock);

		adsp_dbg(dsp, "Shutdown complete\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_early_event);

अटल पूर्णांक wm_adsp2_start_core(काष्ठा wm_adsp *dsp)
अणु
	वापस regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
				 ADSP2_CORE_ENA | ADSP2_START,
				 ADSP2_CORE_ENA | ADSP2_START);
पूर्ण

अटल व्योम wm_adsp2_stop_core(काष्ठा wm_adsp *dsp)
अणु
	regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
			   ADSP2_CORE_ENA | ADSP2_START, 0);
पूर्ण

पूर्णांक wm_adsp_event(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm_adsp *dsps = snd_soc_component_get_drvdata(component);
	काष्ठा wm_adsp *dsp = &dsps[w->shअगरt];
	पूर्णांक ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		flush_work(&dsp->boot_work);

		mutex_lock(&dsp->pwr_lock);

		अगर (!dsp->booted) अणु
			ret = -EIO;
			जाओ err;
		पूर्ण

		अगर (dsp->ops->enable_core) अणु
			ret = dsp->ops->enable_core(dsp);
			अगर (ret != 0)
				जाओ err;
		पूर्ण

		/* Sync set controls */
		ret = wm_coeff_sync_controls(dsp);
		अगर (ret != 0)
			जाओ err;

		अगर (dsp->ops->lock_memory) अणु
			ret = dsp->ops->lock_memory(dsp, dsp->lock_regions);
			अगर (ret != 0) अणु
				adsp_err(dsp, "Error configuring MPU: %d\n",
					 ret);
				जाओ err;
			पूर्ण
		पूर्ण

		अगर (dsp->ops->start_core) अणु
			ret = dsp->ops->start_core(dsp);
			अगर (ret != 0)
				जाओ err;
		पूर्ण

		अगर (wm_adsp_fw[dsp->fw].num_caps != 0) अणु
			ret = wm_adsp_buffer_init(dsp);
			अगर (ret < 0)
				जाओ err;
		पूर्ण

		dsp->running = true;

		mutex_unlock(&dsp->pwr_lock);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		/* Tell the firmware to cleanup */
		wm_adsp_संकेत_event_controls(dsp, WM_ADSP_FW_EVENT_SHUTDOWN);

		अगर (dsp->ops->stop_watchकरोg)
			dsp->ops->stop_watchकरोg(dsp);

		/* Log firmware state, it can be useful क्रम analysis */
		अगर (dsp->ops->show_fw_status)
			dsp->ops->show_fw_status(dsp);

		mutex_lock(&dsp->pwr_lock);

		dsp->running = false;

		अगर (dsp->ops->stop_core)
			dsp->ops->stop_core(dsp);
		अगर (dsp->ops->disable_core)
			dsp->ops->disable_core(dsp);

		अगर (wm_adsp_fw[dsp->fw].num_caps != 0)
			wm_adsp_buffer_मुक्त(dsp);

		dsp->fatal_error = false;

		mutex_unlock(&dsp->pwr_lock);

		adsp_dbg(dsp, "Execution stopped\n");
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
err:
	अगर (dsp->ops->stop_core)
		dsp->ops->stop_core(dsp);
	अगर (dsp->ops->disable_core)
		dsp->ops->disable_core(dsp);
	mutex_unlock(&dsp->pwr_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_event);

अटल पूर्णांक wm_halo_start_core(काष्ठा wm_adsp *dsp)
अणु
	वापस regmap_update_bits(dsp->regmap,
				  dsp->base + HALO_CCM_CORE_CONTROL,
				  HALO_CORE_EN, HALO_CORE_EN);
पूर्ण

अटल व्योम wm_halo_stop_core(काष्ठा wm_adsp *dsp)
अणु
	regmap_update_bits(dsp->regmap, dsp->base + HALO_CCM_CORE_CONTROL,
			   HALO_CORE_EN, 0);

	/* reset halo core with CORE_SOFT_RESET */
	regmap_update_bits(dsp->regmap, dsp->base + HALO_CORE_SOFT_RESET,
			   HALO_CORE_SOFT_RESET_MASK, 1);
पूर्ण

पूर्णांक wm_adsp2_component_probe(काष्ठा wm_adsp *dsp, काष्ठा snd_soc_component *component)
अणु
	अक्षर preload[32];

	snम_लिखो(preload, ARRAY_SIZE(preload), "%s Preload", dsp->name);
	snd_soc_component_disable_pin(component, preload);

	wm_adsp2_init_debugfs(dsp, component);

	dsp->component = component;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp2_component_probe);

पूर्णांक wm_adsp2_component_हटाओ(काष्ठा wm_adsp *dsp, काष्ठा snd_soc_component *component)
अणु
	wm_adsp2_cleanup_debugfs(dsp);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp2_component_हटाओ);

पूर्णांक wm_adsp2_init(काष्ठा wm_adsp *dsp)
अणु
	पूर्णांक ret;

	ret = wm_adsp_common_init(dsp);
	अगर (ret)
		वापस ret;

	चयन (dsp->rev) अणु
	हाल 0:
		/*
		 * Disable the DSP memory by शेष when in reset क्रम a small
		 * घातer saving.
		 */
		ret = regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
					 ADSP2_MEM_ENA, 0);
		अगर (ret) अणु
			adsp_err(dsp,
				 "Failed to clear memory retention: %d\n", ret);
			वापस ret;
		पूर्ण

		dsp->ops = &wm_adsp2_ops[0];
		अवरोध;
	हाल 1:
		dsp->ops = &wm_adsp2_ops[1];
		अवरोध;
	शेष:
		dsp->ops = &wm_adsp2_ops[2];
		अवरोध;
	पूर्ण

	INIT_WORK(&dsp->boot_work, wm_adsp_boot_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp2_init);

पूर्णांक wm_halo_init(काष्ठा wm_adsp *dsp)
अणु
	पूर्णांक ret;

	ret = wm_adsp_common_init(dsp);
	अगर (ret)
		वापस ret;

	dsp->ops = &wm_halo_ops;

	INIT_WORK(&dsp->boot_work, wm_adsp_boot_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_halo_init);

व्योम wm_adsp2_हटाओ(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_coeff_ctl *ctl;

	जबतक (!list_empty(&dsp->ctl_list)) अणु
		ctl = list_first_entry(&dsp->ctl_list, काष्ठा wm_coeff_ctl,
					list);
		list_del(&ctl->list);
		wm_adsp_मुक्त_ctl_blk(ctl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp2_हटाओ);

अटल अंतरभूत पूर्णांक wm_adsp_compr_attached(काष्ठा wm_adsp_compr *compr)
अणु
	वापस compr->buf != शून्य;
पूर्ण

अटल पूर्णांक wm_adsp_compr_attach(काष्ठा wm_adsp_compr *compr)
अणु
	काष्ठा wm_adsp_compr_buf *buf = शून्य, *पंचांगp;

	अगर (compr->dsp->fatal_error)
		वापस -EINVAL;

	list_क्रम_each_entry(पंचांगp, &compr->dsp->buffer_list, list) अणु
		अगर (!पंचांगp->name || !म_भेद(compr->name, पंचांगp->name)) अणु
			buf = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!buf)
		वापस -EINVAL;

	compr->buf = buf;
	buf->compr = compr;

	वापस 0;
पूर्ण

अटल व्योम wm_adsp_compr_detach(काष्ठा wm_adsp_compr *compr)
अणु
	अगर (!compr)
		वापस;

	/* Wake the poll so it can see buffer is no दीर्घer attached */
	अगर (compr->stream)
		snd_compr_fragment_elapsed(compr->stream);

	अगर (wm_adsp_compr_attached(compr)) अणु
		compr->buf->compr = शून्य;
		compr->buf = शून्य;
	पूर्ण
पूर्ण

पूर्णांक wm_adsp_compr_खोलो(काष्ठा wm_adsp *dsp, काष्ठा snd_compr_stream *stream)
अणु
	काष्ठा wm_adsp_compr *compr, *पंचांगp;
	काष्ठा snd_soc_pcm_runसमय *rtd = stream->निजी_data;
	पूर्णांक ret = 0;

	mutex_lock(&dsp->pwr_lock);

	अगर (wm_adsp_fw[dsp->fw].num_caps == 0) अणु
		adsp_err(dsp, "%s: Firmware does not support compressed API\n",
			 asoc_rtd_to_codec(rtd, 0)->name);
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (wm_adsp_fw[dsp->fw].compr_direction != stream->direction) अणु
		adsp_err(dsp, "%s: Firmware does not support stream direction\n",
			 asoc_rtd_to_codec(rtd, 0)->name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(पंचांगp, &dsp->compr_list, list) अणु
		अगर (!म_भेद(पंचांगp->name, asoc_rtd_to_codec(rtd, 0)->name)) अणु
			adsp_err(dsp, "%s: Only a single stream supported per dai\n",
				 asoc_rtd_to_codec(rtd, 0)->name);
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	compr = kzalloc(माप(*compr), GFP_KERNEL);
	अगर (!compr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	compr->dsp = dsp;
	compr->stream = stream;
	compr->name = asoc_rtd_to_codec(rtd, 0)->name;

	list_add_tail(&compr->list, &dsp->compr_list);

	stream->runसमय->निजी_data = compr;

out:
	mutex_unlock(&dsp->pwr_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_compr_खोलो);

पूर्णांक wm_adsp_compr_मुक्त(काष्ठा snd_soc_component *component,
		       काष्ठा snd_compr_stream *stream)
अणु
	काष्ठा wm_adsp_compr *compr = stream->runसमय->निजी_data;
	काष्ठा wm_adsp *dsp = compr->dsp;

	mutex_lock(&dsp->pwr_lock);

	wm_adsp_compr_detach(compr);
	list_del(&compr->list);

	kमुक्त(compr->raw_buf);
	kमुक्त(compr);

	mutex_unlock(&dsp->pwr_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_compr_मुक्त);

अटल पूर्णांक wm_adsp_compr_check_params(काष्ठा snd_compr_stream *stream,
				      काष्ठा snd_compr_params *params)
अणु
	काष्ठा wm_adsp_compr *compr = stream->runसमय->निजी_data;
	काष्ठा wm_adsp *dsp = compr->dsp;
	स्थिर काष्ठा wm_adsp_fw_caps *caps;
	स्थिर काष्ठा snd_codec_desc *desc;
	पूर्णांक i, j;

	अगर (params->buffer.fragment_size < WM_ADSP_MIN_FRAGMENT_SIZE ||
	    params->buffer.fragment_size > WM_ADSP_MAX_FRAGMENT_SIZE ||
	    params->buffer.fragments < WM_ADSP_MIN_FRAGMENTS ||
	    params->buffer.fragments > WM_ADSP_MAX_FRAGMENTS ||
	    params->buffer.fragment_size % WM_ADSP_DATA_WORD_SIZE) अणु
		compr_err(compr, "Invalid buffer fragsize=%d fragments=%d\n",
			  params->buffer.fragment_size,
			  params->buffer.fragments);

		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < wm_adsp_fw[dsp->fw].num_caps; i++) अणु
		caps = &wm_adsp_fw[dsp->fw].caps[i];
		desc = &caps->desc;

		अगर (caps->id != params->codec.id)
			जारी;

		अगर (stream->direction == SND_COMPRESS_PLAYBACK) अणु
			अगर (desc->max_ch < params->codec.ch_out)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (desc->max_ch < params->codec.ch_in)
				जारी;
		पूर्ण

		अगर (!(desc->क्रमmats & (1 << params->codec.क्रमmat)))
			जारी;

		क्रम (j = 0; j < desc->num_sample_rates; ++j)
			अगर (desc->sample_rates[j] == params->codec.sample_rate)
				वापस 0;
	पूर्ण

	compr_err(compr, "Invalid params id=%u ch=%u,%u rate=%u fmt=%u\n",
		  params->codec.id, params->codec.ch_in, params->codec.ch_out,
		  params->codec.sample_rate, params->codec.क्रमmat);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक wm_adsp_compr_frag_words(काष्ठा wm_adsp_compr *compr)
अणु
	वापस compr->size.fragment_size / WM_ADSP_DATA_WORD_SIZE;
पूर्ण

पूर्णांक wm_adsp_compr_set_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_compr_stream *stream,
			     काष्ठा snd_compr_params *params)
अणु
	काष्ठा wm_adsp_compr *compr = stream->runसमय->निजी_data;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	ret = wm_adsp_compr_check_params(stream, params);
	अगर (ret)
		वापस ret;

	compr->size = params->buffer;

	compr_dbg(compr, "fragment_size=%d fragments=%d\n",
		  compr->size.fragment_size, compr->size.fragments);

	size = wm_adsp_compr_frag_words(compr) * माप(*compr->raw_buf);
	compr->raw_buf = kदो_स्मृति(size, GFP_DMA | GFP_KERNEL);
	अगर (!compr->raw_buf)
		वापस -ENOMEM;

	compr->sample_rate = params->codec.sample_rate;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_compr_set_params);

पूर्णांक wm_adsp_compr_get_caps(काष्ठा snd_soc_component *component,
			   काष्ठा snd_compr_stream *stream,
			   काष्ठा snd_compr_caps *caps)
अणु
	काष्ठा wm_adsp_compr *compr = stream->runसमय->निजी_data;
	पूर्णांक fw = compr->dsp->fw;
	पूर्णांक i;

	अगर (wm_adsp_fw[fw].caps) अणु
		क्रम (i = 0; i < wm_adsp_fw[fw].num_caps; i++)
			caps->codecs[i] = wm_adsp_fw[fw].caps[i].id;

		caps->num_codecs = i;
		caps->direction = wm_adsp_fw[fw].compr_direction;

		caps->min_fragment_size = WM_ADSP_MIN_FRAGMENT_SIZE;
		caps->max_fragment_size = WM_ADSP_MAX_FRAGMENT_SIZE;
		caps->min_fragments = WM_ADSP_MIN_FRAGMENTS;
		caps->max_fragments = WM_ADSP_MAX_FRAGMENTS;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_compr_get_caps);

अटल पूर्णांक wm_adsp_पढ़ो_raw_data_block(काष्ठा wm_adsp *dsp, पूर्णांक mem_type,
				       अचिन्हित पूर्णांक mem_addr,
				       अचिन्हित पूर्णांक num_words, __be32 *data)
अणु
	काष्ठा wm_adsp_region स्थिर *mem = wm_adsp_find_region(dsp, mem_type);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	अगर (!mem)
		वापस -EINVAL;

	reg = dsp->ops->region_to_reg(mem, mem_addr);

	ret = regmap_raw_पढ़ो(dsp->regmap, reg, data,
			      माप(*data) * num_words);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक wm_adsp_पढ़ो_data_word(काष्ठा wm_adsp *dsp, पूर्णांक mem_type,
					 अचिन्हित पूर्णांक mem_addr, u32 *data)
अणु
	__be32 raw;
	पूर्णांक ret;

	ret = wm_adsp_पढ़ो_raw_data_block(dsp, mem_type, mem_addr, 1, &raw);
	अगर (ret < 0)
		वापस ret;

	*data = be32_to_cpu(raw) & 0x00ffffffu;

	वापस 0;
पूर्ण

अटल पूर्णांक wm_adsp_ग_लिखो_data_word(काष्ठा wm_adsp *dsp, पूर्णांक mem_type,
				   अचिन्हित पूर्णांक mem_addr, u32 data)
अणु
	काष्ठा wm_adsp_region स्थिर *mem = wm_adsp_find_region(dsp, mem_type);
	__be32 val = cpu_to_be32(data & 0x00ffffffu);
	अचिन्हित पूर्णांक reg;

	अगर (!mem)
		वापस -EINVAL;

	reg = dsp->ops->region_to_reg(mem, mem_addr);

	वापस regmap_raw_ग_लिखो(dsp->regmap, reg, &val, माप(val));
पूर्ण

अटल अंतरभूत पूर्णांक wm_adsp_buffer_पढ़ो(काष्ठा wm_adsp_compr_buf *buf,
				      अचिन्हित पूर्णांक field_offset, u32 *data)
अणु
	वापस wm_adsp_पढ़ो_data_word(buf->dsp, buf->host_buf_mem_type,
				      buf->host_buf_ptr + field_offset, data);
पूर्ण

अटल अंतरभूत पूर्णांक wm_adsp_buffer_ग_लिखो(काष्ठा wm_adsp_compr_buf *buf,
				       अचिन्हित पूर्णांक field_offset, u32 data)
अणु
	वापस wm_adsp_ग_लिखो_data_word(buf->dsp, buf->host_buf_mem_type,
				       buf->host_buf_ptr + field_offset, data);
पूर्ण

अटल व्योम wm_adsp_हटाओ_padding(u32 *buf, पूर्णांक nwords)
अणु
	स्थिर __be32 *pack_in = (__be32 *)buf;
	u8 *pack_out = (u8 *)buf;
	पूर्णांक i;

	/*
	 * DSP words from the रेजिस्टर map have pad bytes and the data bytes
	 * are in swapped order. This swaps back to the original little-endian
	 * order and strips the pad bytes.
	 */
	क्रम (i = 0; i < nwords; i++) अणु
		u32 word = be32_to_cpu(*pack_in++);
		*pack_out++ = (u8)word;
		*pack_out++ = (u8)(word >> 8);
		*pack_out++ = (u8)(word >> 16);
	पूर्ण
पूर्ण

अटल पूर्णांक wm_adsp_buffer_populate(काष्ठा wm_adsp_compr_buf *buf)
अणु
	स्थिर काष्ठा wm_adsp_fw_caps *caps = wm_adsp_fw[buf->dsp->fw].caps;
	काष्ठा wm_adsp_buffer_region *region;
	u32 offset = 0;
	पूर्णांक i, ret;

	buf->regions = kसुस्मृति(caps->num_regions, माप(*buf->regions),
			       GFP_KERNEL);
	अगर (!buf->regions)
		वापस -ENOMEM;

	क्रम (i = 0; i < caps->num_regions; ++i) अणु
		region = &buf->regions[i];

		region->offset = offset;
		region->mem_type = caps->region_defs[i].mem_type;

		ret = wm_adsp_buffer_पढ़ो(buf, caps->region_defs[i].base_offset,
					  &region->base_addr);
		अगर (ret < 0)
			वापस ret;

		ret = wm_adsp_buffer_पढ़ो(buf, caps->region_defs[i].size_offset,
					  &offset);
		अगर (ret < 0)
			वापस ret;

		region->cumulative_size = offset;

		compr_dbg(buf,
			  "region=%d type=%d base=%08x off=%08x size=%08x\n",
			  i, region->mem_type, region->base_addr,
			  region->offset, region->cumulative_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wm_adsp_buffer_clear(काष्ठा wm_adsp_compr_buf *buf)
अणु
	buf->irq_count = 0xFFFFFFFF;
	buf->पढ़ो_index = -1;
	buf->avail = 0;
पूर्ण

अटल काष्ठा wm_adsp_compr_buf *wm_adsp_buffer_alloc(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_adsp_compr_buf *buf;

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->dsp = dsp;

	wm_adsp_buffer_clear(buf);

	list_add_tail(&buf->list, &dsp->buffer_list);

	वापस buf;
पूर्ण

अटल पूर्णांक wm_adsp_buffer_parse_legacy(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_adsp_alg_region *alg_region;
	काष्ठा wm_adsp_compr_buf *buf;
	u32 xmalg, addr, magic;
	पूर्णांक i, ret;

	alg_region = wm_adsp_find_alg_region(dsp, WMFW_ADSP2_XM, dsp->fw_id);
	अगर (!alg_region) अणु
		adsp_err(dsp, "No algorithm region found\n");
		वापस -EINVAL;
	पूर्ण

	buf = wm_adsp_buffer_alloc(dsp);
	अगर (!buf)
		वापस -ENOMEM;

	xmalg = dsp->ops->sys_config_size / माप(__be32);

	addr = alg_region->base + xmalg + ALG_XM_FIELD(magic);
	ret = wm_adsp_पढ़ो_data_word(dsp, WMFW_ADSP2_XM, addr, &magic);
	अगर (ret < 0)
		वापस ret;

	अगर (magic != WM_ADSP_ALG_XM_STRUCT_MAGIC)
		वापस -ENODEV;

	addr = alg_region->base + xmalg + ALG_XM_FIELD(host_buf_ptr);
	क्रम (i = 0; i < 5; ++i) अणु
		ret = wm_adsp_पढ़ो_data_word(dsp, WMFW_ADSP2_XM, addr,
					     &buf->host_buf_ptr);
		अगर (ret < 0)
			वापस ret;

		अगर (buf->host_buf_ptr)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण

	अगर (!buf->host_buf_ptr)
		वापस -EIO;

	buf->host_buf_mem_type = WMFW_ADSP2_XM;

	ret = wm_adsp_buffer_populate(buf);
	अगर (ret < 0)
		वापस ret;

	compr_dbg(buf, "legacy host_buf_ptr=%x\n", buf->host_buf_ptr);

	वापस 0;
पूर्ण

अटल पूर्णांक wm_adsp_buffer_parse_coeff(काष्ठा wm_coeff_ctl *ctl)
अणु
	काष्ठा wm_adsp_host_buf_coeff_v1 coeff_v1;
	काष्ठा wm_adsp_compr_buf *buf;
	अचिन्हित पूर्णांक reg, version;
	__be32 bufp;
	पूर्णांक ret, i;

	ret = wm_coeff_base_reg(ctl, &reg);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < 5; ++i) अणु
		ret = regmap_raw_पढ़ो(ctl->dsp->regmap, reg, &bufp, माप(bufp));
		अगर (ret < 0)
			वापस ret;

		अगर (bufp)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण

	अगर (!bufp) अणु
		adsp_err(ctl->dsp, "Failed to acquire host buffer\n");
		वापस -EIO;
	पूर्ण

	buf = wm_adsp_buffer_alloc(ctl->dsp);
	अगर (!buf)
		वापस -ENOMEM;

	buf->host_buf_mem_type = ctl->alg_region.type;
	buf->host_buf_ptr = be32_to_cpu(bufp);

	ret = wm_adsp_buffer_populate(buf);
	अगर (ret < 0)
		वापस ret;

	/*
	 * v0 host_buffer coefficients didn't have versioning, so अगर the
	 * control is one word, assume version 0.
	 */
	अगर (ctl->len == 4) अणु
		compr_dbg(buf, "host_buf_ptr=%x\n", buf->host_buf_ptr);
		वापस 0;
	पूर्ण

	ret = regmap_raw_पढ़ो(ctl->dsp->regmap, reg, &coeff_v1,
			      माप(coeff_v1));
	अगर (ret < 0)
		वापस ret;

	version = be32_to_cpu(coeff_v1.versions) & HOST_BUF_COEFF_COMPAT_VER_MASK;
	version >>= HOST_BUF_COEFF_COMPAT_VER_SHIFT;

	अगर (version > HOST_BUF_COEFF_SUPPORTED_COMPAT_VER) अणु
		adsp_err(ctl->dsp,
			 "Host buffer coeff ver %u > supported version %u\n",
			 version, HOST_BUF_COEFF_SUPPORTED_COMPAT_VER);
		वापस -EINVAL;
	पूर्ण

	wm_adsp_हटाओ_padding((u32 *)&coeff_v1.name, ARRAY_SIZE(coeff_v1.name));

	buf->name = kaप्र_लिखो(GFP_KERNEL, "%s-dsp-%s", ctl->dsp->part,
			      (अक्षर *)&coeff_v1.name);

	compr_dbg(buf, "host_buf_ptr=%x coeff version %u\n",
		  buf->host_buf_ptr, version);

	वापस version;
पूर्ण

अटल पूर्णांक wm_adsp_buffer_init(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_coeff_ctl *ctl;
	पूर्णांक ret;

	list_क्रम_each_entry(ctl, &dsp->ctl_list, list) अणु
		अगर (ctl->type != WMFW_CTL_TYPE_HOST_BUFFER)
			जारी;

		अगर (!ctl->enabled)
			जारी;

		ret = wm_adsp_buffer_parse_coeff(ctl);
		अगर (ret < 0) अणु
			adsp_err(dsp, "Failed to parse coeff: %d\n", ret);
			जाओ error;
		पूर्ण अन्यथा अगर (ret == 0) अणु
			/* Only one buffer supported क्रम version 0 */
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (list_empty(&dsp->buffer_list)) अणु
		/* Fall back to legacy support */
		ret = wm_adsp_buffer_parse_legacy(dsp);
		अगर (ret) अणु
			adsp_err(dsp, "Failed to parse legacy: %d\n", ret);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	wm_adsp_buffer_मुक्त(dsp);
	वापस ret;
पूर्ण

अटल पूर्णांक wm_adsp_buffer_मुक्त(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_adsp_compr_buf *buf, *पंचांगp;

	list_क्रम_each_entry_safe(buf, पंचांगp, &dsp->buffer_list, list) अणु
		wm_adsp_compr_detach(buf->compr);

		kमुक्त(buf->name);
		kमुक्त(buf->regions);
		list_del(&buf->list);
		kमुक्त(buf);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm_adsp_buffer_get_error(काष्ठा wm_adsp_compr_buf *buf)
अणु
	पूर्णांक ret;

	ret = wm_adsp_buffer_पढ़ो(buf, HOST_BUFFER_FIELD(error), &buf->error);
	अगर (ret < 0) अणु
		compr_err(buf, "Failed to check buffer error: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (buf->error != 0) अणु
		compr_err(buf, "Buffer error occurred: %d\n", buf->error);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wm_adsp_compr_trigger(काष्ठा snd_soc_component *component,
			  काष्ठा snd_compr_stream *stream, पूर्णांक cmd)
अणु
	काष्ठा wm_adsp_compr *compr = stream->runसमय->निजी_data;
	काष्ठा wm_adsp *dsp = compr->dsp;
	पूर्णांक ret = 0;

	compr_dbg(compr, "Trigger: %d\n", cmd);

	mutex_lock(&dsp->pwr_lock);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (!wm_adsp_compr_attached(compr)) अणु
			ret = wm_adsp_compr_attach(compr);
			अगर (ret < 0) अणु
				compr_err(compr, "Failed to link buffer and stream: %d\n",
					  ret);
				अवरोध;
			पूर्ण
		पूर्ण

		ret = wm_adsp_buffer_get_error(compr->buf);
		अगर (ret < 0)
			अवरोध;

		/* Trigger the IRQ at one fragment of data */
		ret = wm_adsp_buffer_ग_लिखो(compr->buf,
					   HOST_BUFFER_FIELD(high_water_mark),
					   wm_adsp_compr_frag_words(compr));
		अगर (ret < 0) अणु
			compr_err(compr, "Failed to set high water mark: %d\n",
				  ret);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (wm_adsp_compr_attached(compr))
			wm_adsp_buffer_clear(compr->buf);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&dsp->pwr_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_compr_trigger);

अटल अंतरभूत पूर्णांक wm_adsp_buffer_size(काष्ठा wm_adsp_compr_buf *buf)
अणु
	पूर्णांक last_region = wm_adsp_fw[buf->dsp->fw].caps->num_regions - 1;

	वापस buf->regions[last_region].cumulative_size;
पूर्ण

अटल पूर्णांक wm_adsp_buffer_update_avail(काष्ठा wm_adsp_compr_buf *buf)
अणु
	u32 next_पढ़ो_index, next_ग_लिखो_index;
	पूर्णांक ग_लिखो_index, पढ़ो_index, avail;
	पूर्णांक ret;

	/* Only sync पढ़ो index अगर we haven't alपढ़ोy पढ़ो a valid index */
	अगर (buf->पढ़ो_index < 0) अणु
		ret = wm_adsp_buffer_पढ़ो(buf,
				HOST_BUFFER_FIELD(next_पढ़ो_index),
				&next_पढ़ो_index);
		अगर (ret < 0)
			वापस ret;

		पढ़ो_index = sign_extend32(next_पढ़ो_index, 23);

		अगर (पढ़ो_index < 0) अणु
			compr_dbg(buf, "Avail check on unstarted stream\n");
			वापस 0;
		पूर्ण

		buf->पढ़ो_index = पढ़ो_index;
	पूर्ण

	ret = wm_adsp_buffer_पढ़ो(buf, HOST_BUFFER_FIELD(next_ग_लिखो_index),
			&next_ग_लिखो_index);
	अगर (ret < 0)
		वापस ret;

	ग_लिखो_index = sign_extend32(next_ग_लिखो_index, 23);

	avail = ग_लिखो_index - buf->पढ़ो_index;
	अगर (avail < 0)
		avail += wm_adsp_buffer_size(buf);

	compr_dbg(buf, "readindex=0x%x, writeindex=0x%x, avail=%d\n",
		  buf->पढ़ो_index, ग_लिखो_index, avail * WM_ADSP_DATA_WORD_SIZE);

	buf->avail = avail;

	वापस 0;
पूर्ण

पूर्णांक wm_adsp_compr_handle_irq(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_adsp_compr_buf *buf;
	काष्ठा wm_adsp_compr *compr;
	पूर्णांक ret = 0;

	mutex_lock(&dsp->pwr_lock);

	अगर (list_empty(&dsp->buffer_list)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	adsp_dbg(dsp, "Handling buffer IRQ\n");

	list_क्रम_each_entry(buf, &dsp->buffer_list, list) अणु
		compr = buf->compr;

		ret = wm_adsp_buffer_get_error(buf);
		अगर (ret < 0)
			जाओ out_notअगरy; /* Wake poll to report error */

		ret = wm_adsp_buffer_पढ़ो(buf, HOST_BUFFER_FIELD(irq_count),
					  &buf->irq_count);
		अगर (ret < 0) अणु
			compr_err(buf, "Failed to get irq_count: %d\n", ret);
			जाओ out;
		पूर्ण

		ret = wm_adsp_buffer_update_avail(buf);
		अगर (ret < 0) अणु
			compr_err(buf, "Error reading avail: %d\n", ret);
			जाओ out;
		पूर्ण

		अगर (wm_adsp_fw[dsp->fw].voice_trigger && buf->irq_count == 2)
			ret = WM_ADSP_COMPR_VOICE_TRIGGER;

out_notअगरy:
		अगर (compr && compr->stream)
			snd_compr_fragment_elapsed(compr->stream);
	पूर्ण

out:
	mutex_unlock(&dsp->pwr_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_compr_handle_irq);

अटल पूर्णांक wm_adsp_buffer_reenable_irq(काष्ठा wm_adsp_compr_buf *buf)
अणु
	अगर (buf->irq_count & 0x01)
		वापस 0;

	compr_dbg(buf, "Enable IRQ(0x%x) for next fragment\n", buf->irq_count);

	buf->irq_count |= 0x01;

	वापस wm_adsp_buffer_ग_लिखो(buf, HOST_BUFFER_FIELD(irq_ack),
				    buf->irq_count);
पूर्ण

पूर्णांक wm_adsp_compr_poपूर्णांकer(काष्ठा snd_soc_component *component,
			  काष्ठा snd_compr_stream *stream,
			  काष्ठा snd_compr_tstamp *tstamp)
अणु
	काष्ठा wm_adsp_compr *compr = stream->runसमय->निजी_data;
	काष्ठा wm_adsp *dsp = compr->dsp;
	काष्ठा wm_adsp_compr_buf *buf;
	पूर्णांक ret = 0;

	compr_dbg(compr, "Pointer request\n");

	mutex_lock(&dsp->pwr_lock);

	buf = compr->buf;

	अगर (dsp->fatal_error || !buf || buf->error) अणु
		snd_compr_stop_error(stream, SNDRV_PCM_STATE_XRUN);
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (buf->avail < wm_adsp_compr_frag_words(compr)) अणु
		ret = wm_adsp_buffer_update_avail(buf);
		अगर (ret < 0) अणु
			compr_err(compr, "Error reading avail: %d\n", ret);
			जाओ out;
		पूर्ण

		/*
		 * If we really have less than 1 fragment available tell the
		 * DSP to inक्रमm us once a whole fragment is available.
		 */
		अगर (buf->avail < wm_adsp_compr_frag_words(compr)) अणु
			ret = wm_adsp_buffer_get_error(buf);
			अगर (ret < 0) अणु
				अगर (buf->error)
					snd_compr_stop_error(stream,
							SNDRV_PCM_STATE_XRUN);
				जाओ out;
			पूर्ण

			ret = wm_adsp_buffer_reenable_irq(buf);
			अगर (ret < 0) अणु
				compr_err(compr, "Failed to re-enable buffer IRQ: %d\n",
					  ret);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	tstamp->copied_total = compr->copied_total;
	tstamp->copied_total += buf->avail * WM_ADSP_DATA_WORD_SIZE;
	tstamp->sampling_rate = compr->sample_rate;

out:
	mutex_unlock(&dsp->pwr_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_compr_poपूर्णांकer);

अटल पूर्णांक wm_adsp_buffer_capture_block(काष्ठा wm_adsp_compr *compr, पूर्णांक target)
अणु
	काष्ठा wm_adsp_compr_buf *buf = compr->buf;
	अचिन्हित पूर्णांक adsp_addr;
	पूर्णांक mem_type, nwords, max_पढ़ो;
	पूर्णांक i, ret;

	/* Calculate पढ़ो parameters */
	क्रम (i = 0; i < wm_adsp_fw[buf->dsp->fw].caps->num_regions; ++i)
		अगर (buf->पढ़ो_index < buf->regions[i].cumulative_size)
			अवरोध;

	अगर (i == wm_adsp_fw[buf->dsp->fw].caps->num_regions)
		वापस -EINVAL;

	mem_type = buf->regions[i].mem_type;
	adsp_addr = buf->regions[i].base_addr +
		    (buf->पढ़ो_index - buf->regions[i].offset);

	max_पढ़ो = wm_adsp_compr_frag_words(compr);
	nwords = buf->regions[i].cumulative_size - buf->पढ़ो_index;

	अगर (nwords > target)
		nwords = target;
	अगर (nwords > buf->avail)
		nwords = buf->avail;
	अगर (nwords > max_पढ़ो)
		nwords = max_पढ़ो;
	अगर (!nwords)
		वापस 0;

	/* Read data from DSP */
	ret = wm_adsp_पढ़ो_raw_data_block(buf->dsp, mem_type, adsp_addr,
					  nwords, (__be32 *)compr->raw_buf);
	अगर (ret < 0)
		वापस ret;

	wm_adsp_हटाओ_padding(compr->raw_buf, nwords);

	/* update पढ़ो index to account क्रम words पढ़ो */
	buf->पढ़ो_index += nwords;
	अगर (buf->पढ़ो_index == wm_adsp_buffer_size(buf))
		buf->पढ़ो_index = 0;

	ret = wm_adsp_buffer_ग_लिखो(buf, HOST_BUFFER_FIELD(next_पढ़ो_index),
				   buf->पढ़ो_index);
	अगर (ret < 0)
		वापस ret;

	/* update avail to account क्रम words पढ़ो */
	buf->avail -= nwords;

	वापस nwords;
पूर्ण

अटल पूर्णांक wm_adsp_compr_पढ़ो(काष्ठा wm_adsp_compr *compr,
			      अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा wm_adsp *dsp = compr->dsp;
	पूर्णांक ntotal = 0;
	पूर्णांक nwords, nbytes;

	compr_dbg(compr, "Requested read of %zu bytes\n", count);

	अगर (dsp->fatal_error || !compr->buf || compr->buf->error) अणु
		snd_compr_stop_error(compr->stream, SNDRV_PCM_STATE_XRUN);
		वापस -EIO;
	पूर्ण

	count /= WM_ADSP_DATA_WORD_SIZE;

	करो अणु
		nwords = wm_adsp_buffer_capture_block(compr, count);
		अगर (nwords < 0) अणु
			compr_err(compr, "Failed to capture block: %d\n",
				  nwords);
			वापस nwords;
		पूर्ण

		nbytes = nwords * WM_ADSP_DATA_WORD_SIZE;

		compr_dbg(compr, "Read %d bytes\n", nbytes);

		अगर (copy_to_user(buf + ntotal, compr->raw_buf, nbytes)) अणु
			compr_err(compr, "Failed to copy data to user: %d, %d\n",
				  ntotal, nbytes);
			वापस -EFAULT;
		पूर्ण

		count -= nwords;
		ntotal += nbytes;
	पूर्ण जबतक (nwords > 0 && count > 0);

	compr->copied_total += ntotal;

	वापस ntotal;
पूर्ण

पूर्णांक wm_adsp_compr_copy(काष्ठा snd_soc_component *component,
		       काष्ठा snd_compr_stream *stream, अक्षर __user *buf,
		       माप_प्रकार count)
अणु
	काष्ठा wm_adsp_compr *compr = stream->runसमय->निजी_data;
	काष्ठा wm_adsp *dsp = compr->dsp;
	पूर्णांक ret;

	mutex_lock(&dsp->pwr_lock);

	अगर (stream->direction == SND_COMPRESS_CAPTURE)
		ret = wm_adsp_compr_पढ़ो(compr, buf, count);
	अन्यथा
		ret = -ENOTSUPP;

	mutex_unlock(&dsp->pwr_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp_compr_copy);

अटल व्योम wm_adsp_fatal_error(काष्ठा wm_adsp *dsp)
अणु
	काष्ठा wm_adsp_compr *compr;

	dsp->fatal_error = true;

	list_क्रम_each_entry(compr, &dsp->compr_list, list) अणु
		अगर (compr->stream)
			snd_compr_fragment_elapsed(compr->stream);
	पूर्ण
पूर्ण

irqवापस_t wm_adsp2_bus_error(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm_adsp *dsp = (काष्ठा wm_adsp *)data;
	अचिन्हित पूर्णांक val;
	काष्ठा regmap *regmap = dsp->regmap;
	पूर्णांक ret = 0;

	mutex_lock(&dsp->pwr_lock);

	ret = regmap_पढ़ो(regmap, dsp->base + ADSP2_LOCK_REGION_CTRL, &val);
	अगर (ret) अणु
		adsp_err(dsp,
			"Failed to read Region Lock Ctrl register: %d\n", ret);
		जाओ error;
	पूर्ण

	अगर (val & ADSP2_WDT_TIMEOUT_STS_MASK) अणु
		adsp_err(dsp, "watchdog timeout error\n");
		dsp->ops->stop_watchकरोg(dsp);
		wm_adsp_fatal_error(dsp);
	पूर्ण

	अगर (val & (ADSP2_ADDR_ERR_MASK | ADSP2_REGION_LOCK_ERR_MASK)) अणु
		अगर (val & ADSP2_ADDR_ERR_MASK)
			adsp_err(dsp, "bus error: address error\n");
		अन्यथा
			adsp_err(dsp, "bus error: region lock error\n");

		ret = regmap_पढ़ो(regmap, dsp->base + ADSP2_BUS_ERR_ADDR, &val);
		अगर (ret) अणु
			adsp_err(dsp,
				 "Failed to read Bus Err Addr register: %d\n",
				 ret);
			जाओ error;
		पूर्ण

		adsp_err(dsp, "bus error address = 0x%x\n",
			 val & ADSP2_BUS_ERR_ADDR_MASK);

		ret = regmap_पढ़ो(regmap,
				  dsp->base + ADSP2_PMEM_ERR_ADDR_XMEM_ERR_ADDR,
				  &val);
		अगर (ret) अणु
			adsp_err(dsp,
				 "Failed to read Pmem Xmem Err Addr register: %d\n",
				 ret);
			जाओ error;
		पूर्ण

		adsp_err(dsp, "xmem error address = 0x%x\n",
			 val & ADSP2_XMEM_ERR_ADDR_MASK);
		adsp_err(dsp, "pmem error address = 0x%x\n",
			 (val & ADSP2_PMEM_ERR_ADDR_MASK) >>
			 ADSP2_PMEM_ERR_ADDR_SHIFT);
	पूर्ण

	regmap_update_bits(regmap, dsp->base + ADSP2_LOCK_REGION_CTRL,
			   ADSP2_CTRL_ERR_EINT, ADSP2_CTRL_ERR_EINT);

error:
	mutex_unlock(&dsp->pwr_lock);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(wm_adsp2_bus_error);

irqवापस_t wm_halo_bus_error(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm_adsp *dsp = (काष्ठा wm_adsp *)data;
	काष्ठा regmap *regmap = dsp->regmap;
	अचिन्हित पूर्णांक fault[6];
	काष्ठा reg_sequence clear[] = अणु
		अणु dsp->base + HALO_MPU_XM_VIO_STATUS,     0x0 पूर्ण,
		अणु dsp->base + HALO_MPU_YM_VIO_STATUS,     0x0 पूर्ण,
		अणु dsp->base + HALO_MPU_PM_VIO_STATUS,     0x0 पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&dsp->pwr_lock);

	ret = regmap_पढ़ो(regmap, dsp->base_sysinfo + HALO_AHBM_WINDOW_DEBUG_1,
			  fault);
	अगर (ret) अणु
		adsp_warn(dsp, "Failed to read AHB DEBUG_1: %d\n", ret);
		जाओ निकास_unlock;
	पूर्ण

	adsp_warn(dsp, "AHB: STATUS: 0x%x ADDR: 0x%x\n",
		  *fault & HALO_AHBM_FLAGS_ERR_MASK,
		  (*fault & HALO_AHBM_CORE_ERR_ADDR_MASK) >>
		  HALO_AHBM_CORE_ERR_ADDR_SHIFT);

	ret = regmap_पढ़ो(regmap, dsp->base_sysinfo + HALO_AHBM_WINDOW_DEBUG_0,
			  fault);
	अगर (ret) अणु
		adsp_warn(dsp, "Failed to read AHB DEBUG_0: %d\n", ret);
		जाओ निकास_unlock;
	पूर्ण

	adsp_warn(dsp, "AHB: SYS_ADDR: 0x%x\n", *fault);

	ret = regmap_bulk_पढ़ो(regmap, dsp->base + HALO_MPU_XM_VIO_ADDR,
			       fault, ARRAY_SIZE(fault));
	अगर (ret) अणु
		adsp_warn(dsp, "Failed to read MPU fault info: %d\n", ret);
		जाओ निकास_unlock;
	पूर्ण

	adsp_warn(dsp, "XM: STATUS:0x%x ADDR:0x%x\n", fault[1], fault[0]);
	adsp_warn(dsp, "YM: STATUS:0x%x ADDR:0x%x\n", fault[3], fault[2]);
	adsp_warn(dsp, "PM: STATUS:0x%x ADDR:0x%x\n", fault[5], fault[4]);

	ret = regmap_multi_reg_ग_लिखो(dsp->regmap, clear, ARRAY_SIZE(clear));
	अगर (ret)
		adsp_warn(dsp, "Failed to clear MPU status: %d\n", ret);

निकास_unlock:
	mutex_unlock(&dsp->pwr_lock);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(wm_halo_bus_error);

irqवापस_t wm_halo_wdt_expire(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm_adsp *dsp = data;

	mutex_lock(&dsp->pwr_lock);

	adsp_warn(dsp, "WDT Expiry Fault\n");
	dsp->ops->stop_watchकरोg(dsp);
	wm_adsp_fatal_error(dsp);

	mutex_unlock(&dsp->pwr_lock);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(wm_halo_wdt_expire);

अटल काष्ठा wm_adsp_ops wm_adsp1_ops = अणु
	.validate_version = wm_adsp_validate_version,
	.parse_sizes = wm_adsp1_parse_sizes,
	.region_to_reg = wm_adsp_region_to_reg,
पूर्ण;

अटल काष्ठा wm_adsp_ops wm_adsp2_ops[] = अणु
	अणु
		.sys_config_size = माप(काष्ठा wm_adsp_प्रणाली_config_xm_hdr),
		.parse_sizes = wm_adsp2_parse_sizes,
		.validate_version = wm_adsp_validate_version,
		.setup_algs = wm_adsp2_setup_algs,
		.region_to_reg = wm_adsp_region_to_reg,

		.show_fw_status = wm_adsp2_show_fw_status,

		.enable_memory = wm_adsp2_enable_memory,
		.disable_memory = wm_adsp2_disable_memory,

		.enable_core = wm_adsp2_enable_core,
		.disable_core = wm_adsp2_disable_core,

		.start_core = wm_adsp2_start_core,
		.stop_core = wm_adsp2_stop_core,

	पूर्ण,
	अणु
		.sys_config_size = माप(काष्ठा wm_adsp_प्रणाली_config_xm_hdr),
		.parse_sizes = wm_adsp2_parse_sizes,
		.validate_version = wm_adsp_validate_version,
		.setup_algs = wm_adsp2_setup_algs,
		.region_to_reg = wm_adsp_region_to_reg,

		.show_fw_status = wm_adsp2v2_show_fw_status,

		.enable_memory = wm_adsp2_enable_memory,
		.disable_memory = wm_adsp2_disable_memory,
		.lock_memory = wm_adsp2_lock,

		.enable_core = wm_adsp2v2_enable_core,
		.disable_core = wm_adsp2v2_disable_core,

		.start_core = wm_adsp2_start_core,
		.stop_core = wm_adsp2_stop_core,
	पूर्ण,
	अणु
		.sys_config_size = माप(काष्ठा wm_adsp_प्रणाली_config_xm_hdr),
		.parse_sizes = wm_adsp2_parse_sizes,
		.validate_version = wm_adsp_validate_version,
		.setup_algs = wm_adsp2_setup_algs,
		.region_to_reg = wm_adsp_region_to_reg,

		.show_fw_status = wm_adsp2v2_show_fw_status,
		.stop_watchकरोg = wm_adsp_stop_watchकरोg,

		.enable_memory = wm_adsp2_enable_memory,
		.disable_memory = wm_adsp2_disable_memory,
		.lock_memory = wm_adsp2_lock,

		.enable_core = wm_adsp2v2_enable_core,
		.disable_core = wm_adsp2v2_disable_core,

		.start_core = wm_adsp2_start_core,
		.stop_core = wm_adsp2_stop_core,
	पूर्ण,
पूर्ण;

अटल काष्ठा wm_adsp_ops wm_halo_ops = अणु
	.sys_config_size = माप(काष्ठा wm_halo_प्रणाली_config_xm_hdr),
	.parse_sizes = wm_adsp2_parse_sizes,
	.validate_version = wm_halo_validate_version,
	.setup_algs = wm_halo_setup_algs,
	.region_to_reg = wm_halo_region_to_reg,

	.show_fw_status = wm_halo_show_fw_status,
	.stop_watchकरोg = wm_halo_stop_watchकरोg,

	.lock_memory = wm_halo_configure_mpu,

	.start_core = wm_halo_start_core,
	.stop_core = wm_halo_stop_core,
पूर्ण;

MODULE_LICENSE("GPL v2");
