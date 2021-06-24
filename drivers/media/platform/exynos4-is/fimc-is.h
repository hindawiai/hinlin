<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Younghwan Joo <yhwan.joo@samsung.com>
 *          Sylwester Nawrocki <s.nawrocki@samsung.com>
 */
#अगर_अघोषित FIMC_IS_H_
#घोषणा FIMC_IS_H_

#समावेश <यंत्र/barrier.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "fimc-isp.h"
#समावेश "fimc-is-command.h"
#समावेश "fimc-is-sensor.h"
#समावेश "fimc-is-param.h"
#समावेश "fimc-is-regs.h"

#घोषणा FIMC_IS_DRV_NAME		"exynos4-fimc-is"

#घोषणा FIMC_IS_FW_खाताNAME		"exynos4_fimc_is_fw.bin"
#घोषणा FIMC_IS_SETखाता_6A3		"exynos4_s5k6a3_setfile.bin"

#घोषणा FIMC_IS_FW_LOAD_TIMEOUT		1000 /* ms */
#घोषणा FIMC_IS_POWER_ON_TIMEOUT	1000 /* us */

#घोषणा FIMC_IS_SENSORS_NUM		2

/* Memory definitions */
#घोषणा FIMC_IS_CPU_MEM_SIZE		(0xa00000)
#घोषणा FIMC_IS_CPU_BASE_MASK		((1 << 26) - 1)
#घोषणा FIMC_IS_REGION_SIZE		0x5000

#घोषणा FIMC_IS_DEBUG_REGION_OFFSET	0x0084b000
#घोषणा FIMC_IS_SHARED_REGION_OFFSET	0x008c0000
#घोषणा FIMC_IS_FW_INFO_LEN		31
#घोषणा FIMC_IS_FW_VER_LEN		7
#घोषणा FIMC_IS_FW_DESC_LEN		(FIMC_IS_FW_INFO_LEN + \
					 FIMC_IS_FW_VER_LEN)
#घोषणा FIMC_IS_SETखाता_INFO_LEN	39

#घोषणा FIMC_IS_EXTRA_MEM_SIZE		(FIMC_IS_EXTRA_FW_SIZE + \
					 FIMC_IS_EXTRA_SETखाता_SIZE + 0x1000)
#घोषणा FIMC_IS_EXTRA_FW_SIZE		0x180000
#घोषणा FIMC_IS_EXTRA_SETखाता_SIZE	0x4b000

/* TODO: revisit */
#घोषणा FIMC_IS_FW_ADDR_MASK		((1 << 26) - 1)
#घोषणा FIMC_IS_FW_SIZE_MAX		(SZ_4M)
#घोषणा FIMC_IS_FW_SIZE_MIN		(SZ_32K)

#घोषणा ATCLK_MCUISP_FREQUENCY		100000000UL
#घोषणा ACLK_AXI_FREQUENCY		100000000UL

क्रमागत अणु
	ISS_CLK_PPMUISPX,
	ISS_CLK_PPMUISPMX,
	ISS_CLK_LITE0,
	ISS_CLK_LITE1,
	ISS_CLK_MPLL,
	ISS_CLK_ISP,
	ISS_CLK_DRC,
	ISS_CLK_FD,
	ISS_CLK_MCUISP,
	ISS_CLK_GICISP,
	ISS_CLK_PWM_ISP,
	ISS_CLK_MCUCTL_ISP,
	ISS_CLK_UART,
	ISS_GATE_CLKS_MAX,
	ISS_CLK_ISP_DIV0 = ISS_GATE_CLKS_MAX,
	ISS_CLK_ISP_DIV1,
	ISS_CLK_MCUISP_DIV0,
	ISS_CLK_MCUISP_DIV1,
	ISS_CLK_ACLK200,
	ISS_CLK_ACLK200_DIV,
	ISS_CLK_ACLK400MCUISP,
	ISS_CLK_ACLK400MCUISP_DIV,
	ISS_CLKS_MAX
पूर्ण;

/* The driver's पूर्णांकernal state flags */
क्रमागत अणु
	IS_ST_IDLE,
	IS_ST_PWR_ON,
	IS_ST_A5_PWR_ON,
	IS_ST_FW_LOADED,
	IS_ST_OPEN_SENSOR,
	IS_ST_SETखाता_LOADED,
	IS_ST_INIT_DONE,
	IS_ST_STREAM_ON,
	IS_ST_STREAM_OFF,
	IS_ST_CHANGE_MODE,
	IS_ST_BLOCK_CMD_CLEARED,
	IS_ST_SET_ZOOM,
	IS_ST_PWR_SUBIP_ON,
	IS_ST_END,
पूर्ण;

क्रमागत af_state अणु
	FIMC_IS_AF_IDLE		= 0,
	FIMC_IS_AF_SETCONFIG	= 1,
	FIMC_IS_AF_RUNNING	= 2,
	FIMC_IS_AF_LOCK		= 3,
	FIMC_IS_AF_ABORT	= 4,
	FIMC_IS_AF_FAILED	= 5,
पूर्ण;

क्रमागत af_lock_state अणु
	FIMC_IS_AF_UNLOCKED	= 0,
	FIMC_IS_AF_LOCKED	= 2
पूर्ण;

क्रमागत ae_lock_state अणु
	FIMC_IS_AE_UNLOCKED	= 0,
	FIMC_IS_AE_LOCKED	= 1
पूर्ण;

क्रमागत awb_lock_state अणु
	FIMC_IS_AWB_UNLOCKED	= 0,
	FIMC_IS_AWB_LOCKED	= 1
पूर्ण;

क्रमागत अणु
	IS_METERING_CONFIG_CMD,
	IS_METERING_CONFIG_WIN_POS_X,
	IS_METERING_CONFIG_WIN_POS_Y,
	IS_METERING_CONFIG_WIN_WIDTH,
	IS_METERING_CONFIG_WIN_HEIGHT,
	IS_METERING_CONFIG_MAX
पूर्ण;

काष्ठा is_setfile अणु
	स्थिर काष्ठा firmware *info;
	पूर्णांक state;
	u32 sub_index;
	u32 base;
	माप_प्रकार size;
पूर्ण;

काष्ठा is_fd_result_header अणु
	u32 offset;
	u32 count;
	u32 index;
	u32 curr_index;
	u32 width;
	u32 height;
पूर्ण;

काष्ठा is_af_info अणु
	u16 mode;
	u32 af_state;
	u32 af_lock_state;
	u32 ae_lock_state;
	u32 awb_lock_state;
	u16 pos_x;
	u16 pos_y;
	u16 prev_pos_x;
	u16 prev_pos_y;
	u16 use_af;
पूर्ण;

काष्ठा fimc_is_firmware अणु
	स्थिर काष्ठा firmware *f_w;

	dma_addr_t addr;
	व्योम *vaddr;
	अचिन्हित पूर्णांक size;

	अक्षर info[FIMC_IS_FW_INFO_LEN + 1];
	अक्षर version[FIMC_IS_FW_VER_LEN + 1];
	अक्षर setfile_info[FIMC_IS_SETखाता_INFO_LEN + 1];
	u8 state;
पूर्ण;

काष्ठा fimc_is_memory अणु
	/* DMA base address */
	dma_addr_t addr;
	/* भव base address */
	व्योम *vaddr;
	/* total length */
	अचिन्हित पूर्णांक size;
पूर्ण;

#घोषणा FIMC_IS_I2H_MAX_ARGS	12

काष्ठा i2h_cmd अणु
	u32 cmd;
	u32 sensor_id;
	u16 num_args;
	u32 args[FIMC_IS_I2H_MAX_ARGS];
पूर्ण;

काष्ठा h2i_cmd अणु
	u16 cmd_type;
	u32 entry_id;
पूर्ण;

#घोषणा FIMC_IS_DEBUG_MSG	0x3f
#घोषणा FIMC_IS_DEBUG_LEVEL	3

काष्ठा fimc_is_setfile अणु
	स्थिर काष्ठा firmware *info;
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक size;
	u32 sub_index;
	u32 base;
पूर्ण;

काष्ठा chain_config अणु
	काष्ठा global_param	global;
	काष्ठा sensor_param	sensor;
	काष्ठा isp_param	isp;
	काष्ठा drc_param	drc;
	काष्ठा fd_param		fd;

	अचिन्हित दीर्घ		p_region_index[2];
पूर्ण;

/**
 * काष्ठा fimc_is - fimc-is data काष्ठाure
 * @pdev: poपूर्णांकer to FIMC-IS platक्रमm device
 * @pctrl: poपूर्णांकer to pinctrl काष्ठाure क्रम this device
 * @v4l2_dev: poपूर्णांकer to the top level v4l2_device
 * @fw: data काष्ठाure describing the FIMC-IS firmware binary
 * @memory: memory region asचिन्हित क्रम the FIMC-IS (firmware)
 * @isp: the ISP block data काष्ठाure
 * @sensor: fimc-is sensor subdevice array
 * @setfile: descriptor of the imaging pipeline calibration data
 * @ctrl_handler: the v4l2 controls handler
 * @lock: mutex serializing video device and the subdev operations
 * @slock: spinlock protecting this data काष्ठाure and the hw रेजिस्टरs
 * @घड़ीs: FIMC-LITE gate घड़ी
 * @regs: MCUCTL mmapped रेजिस्टरs region
 * @pmu_regs: PMU ISP mmapped रेजिस्टरs region
 * @irq: FIMC-IS पूर्णांकerrupt
 * @irq_queue: पूर्णांकerrupt handling रुकोqueue
 * @lpm: low घातer mode flag
 * @state: पूर्णांकernal driver's state flags
 * @sensor_index: image sensor index क्रम the firmware
 * @i2h_cmd: FIMC-IS to the host (CPU) mailbox command data काष्ठाure
 * @h2i_cmd: the host (CPU) to FIMC-IS mailbox command data काष्ठाure
 * @fd_header: the face detection result data काष्ठाure
 * @config: shared HW pipeline configuration data
 * @config_index: index to the @config entry currently in use
 * @is_p_region: poपूर्णांकer to the shared parameter memory region
 * @is_dma_p_region: DMA address of the shared parameter memory region
 * @is_shared_region: poपूर्णांकer to the IS shared region data काष्ठाure
 * @af: स्वतः focus data
 * @debugfs_entry: debugfs entry क्रम the firmware log
 */
काष्ठा fimc_is अणु
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा pinctrl			*pctrl;
	काष्ठा v4l2_device		*v4l2_dev;

	काष्ठा fimc_is_firmware		fw;
	काष्ठा fimc_is_memory		memory;

	काष्ठा fimc_isp			isp;
	काष्ठा fimc_is_sensor		sensor[FIMC_IS_SENSORS_NUM];
	काष्ठा fimc_is_setfile		setfile;

	काष्ठा v4l2_ctrl_handler	ctrl_handler;

	काष्ठा mutex			lock;
	spinlock_t			slock;

	काष्ठा clk			*घड़ीs[ISS_CLKS_MAX];
	व्योम __iomem			*regs;
	व्योम __iomem			*pmu_regs;
	पूर्णांक				irq;
	रुको_queue_head_t		irq_queue;
	u8				lpm;

	अचिन्हित दीर्घ			state;
	अचिन्हित पूर्णांक			sensor_index;

	काष्ठा i2h_cmd			i2h_cmd;
	काष्ठा h2i_cmd			h2i_cmd;
	काष्ठा is_fd_result_header	fd_header;

	काष्ठा chain_config		config[IS_SC_MAX];
	अचिन्हित			config_index;

	काष्ठा is_region		*is_p_region;
	dma_addr_t			is_dma_p_region;
	काष्ठा is_share_region		*is_shared_region;
	काष्ठा is_af_info		af;

	काष्ठा dentry			*debugfs_entry;
पूर्ण;

अटल अंतरभूत काष्ठा fimc_is *fimc_isp_to_is(काष्ठा fimc_isp *isp)
अणु
	वापस container_of(isp, काष्ठा fimc_is, isp);
पूर्ण

अटल अंतरभूत काष्ठा chain_config *__get_curr_is_config(काष्ठा fimc_is *is)
अणु
	वापस &is->config[is->config_index];
पूर्ण

अटल अंतरभूत व्योम fimc_is_mem_barrier(व्योम)
अणु
	mb();
पूर्ण

अटल अंतरभूत व्योम fimc_is_set_param_bit(काष्ठा fimc_is *is, पूर्णांक num)
अणु
	काष्ठा chain_config *cfg = &is->config[is->config_index];

	set_bit(num, &cfg->p_region_index[0]);
पूर्ण

अटल अंतरभूत व्योम fimc_is_set_param_ctrl_cmd(काष्ठा fimc_is *is, पूर्णांक cmd)
अणु
	is->is_p_region->parameter.isp.control.cmd = cmd;
पूर्ण

अटल अंतरभूत व्योम mcuctl_ग_लिखो(u32 v, काष्ठा fimc_is *is, अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(v, is->regs + offset);
पूर्ण

अटल अंतरभूत u32 mcuctl_पढ़ो(काष्ठा fimc_is *is, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(is->regs + offset);
पूर्ण

अटल अंतरभूत व्योम pmuisp_ग_लिखो(u32 v, काष्ठा fimc_is *is, अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(v, is->pmu_regs + offset);
पूर्ण

अटल अंतरभूत u32 pmuisp_पढ़ो(काष्ठा fimc_is *is, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(is->pmu_regs + offset);
पूर्ण

पूर्णांक fimc_is_रुको_event(काष्ठा fimc_is *is, अचिन्हित दीर्घ bit,
		       अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक समयout);
पूर्णांक fimc_is_cpu_set_घातer(काष्ठा fimc_is *is, पूर्णांक on);
पूर्णांक fimc_is_start_firmware(काष्ठा fimc_is *is);
पूर्णांक fimc_is_hw_initialize(काष्ठा fimc_is *is);
व्योम fimc_is_log_dump(स्थिर अक्षर *level, स्थिर व्योम *buf, माप_प्रकार len);

#पूर्ण_अगर /* FIMC_IS_H_ */
