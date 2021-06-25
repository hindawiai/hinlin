<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/semaphore.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/barrier.h>

#समावेश "hinic_hw_csr.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_api_cmd.h"

#घोषणा API_CHAIN_NUM_CELLS                     32

#घोषणा API_CMD_CELL_SIZE_SHIFT                 6
#घोषणा API_CMD_CELL_SIZE_MIN                   (BIT(API_CMD_CELL_SIZE_SHIFT))

#घोषणा API_CMD_CELL_SIZE(cell_size)            \
		(((cell_size) >= API_CMD_CELL_SIZE_MIN) ? \
		 (1 << (fls(cell_size - 1))) : API_CMD_CELL_SIZE_MIN)

#घोषणा API_CMD_CELL_SIZE_VAL(size)             \
		ilog2((size) >> API_CMD_CELL_SIZE_SHIFT)

#घोषणा API_CMD_BUF_SIZE                        2048

/* Sizes of the members in hinic_api_cmd_cell */
#घोषणा API_CMD_CELL_DESC_SIZE          8
#घोषणा API_CMD_CELL_DATA_ADDR_SIZE     8

#घोषणा API_CMD_CELL_ALIGNMENT          8

#घोषणा API_CMD_TIMEOUT                 1000

#घोषणा MASKED_IDX(chain, idx)          ((idx) & ((chain)->num_cells - 1))

#घोषणा SIZE_8BYTES(size)               (ALIGN((size), 8) >> 3)
#घोषणा SIZE_4BYTES(size)               (ALIGN((size), 4) >> 2)

#घोषणा RD_DMA_ATTR_DEFAULT             0
#घोषणा WR_DMA_ATTR_DEFAULT             0

क्रमागत api_cmd_data_क्रमmat अणु
	SGE_DATA = 1,           /* cell data is passed by hw address */
पूर्ण;

क्रमागत api_cmd_type अणु
	API_CMD_WRITE = 0,
पूर्ण;

क्रमागत api_cmd_bypass अणु
	NO_BYPASS       = 0,
	BYPASS          = 1,
पूर्ण;

क्रमागत api_cmd_xor_chk_level अणु
	XOR_CHK_DIS = 0,

	XOR_CHK_ALL = 3,
पूर्ण;

अटल u8 xor_chksum_set(व्योम *data)
अणु
	पूर्णांक idx;
	u8 *val, checksum = 0;

	val = data;

	क्रम (idx = 0; idx < 7; idx++)
		checksum ^= val[idx];

	वापस checksum;
पूर्ण

अटल व्योम set_prod_idx(काष्ठा hinic_api_cmd_chain *chain)
अणु
	क्रमागत hinic_api_cmd_chain_type chain_type = chain->chain_type;
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	u32 addr, prod_idx;

	addr = HINIC_CSR_API_CMD_CHAIN_PI_ADDR(chain_type);
	prod_idx = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	prod_idx = HINIC_API_CMD_PI_CLEAR(prod_idx, IDX);

	prod_idx |= HINIC_API_CMD_PI_SET(chain->prod_idx, IDX);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, prod_idx);
पूर्ण

अटल u32 get_hw_cons_idx(काष्ठा hinic_api_cmd_chain *chain)
अणु
	u32 addr, val;

	addr = HINIC_CSR_API_CMD_STATUS_ADDR(chain->chain_type);
	val  = hinic_hwअगर_पढ़ो_reg(chain->hwअगर, addr);

	वापस HINIC_API_CMD_STATUS_GET(val, CONS_IDX);
पूर्ण

अटल व्योम dump_api_chain_reg(काष्ठा hinic_api_cmd_chain *chain)
अणु
	u32 addr, val;

	addr = HINIC_CSR_API_CMD_STATUS_ADDR(chain->chain_type);
	val  = hinic_hwअगर_पढ़ो_reg(chain->hwअगर, addr);

	dev_err(&chain->hwअगर->pdev->dev, "Chain type: 0x%x, cpld error: 0x%x, check error: 0x%x, current fsm: 0x%x\n",
		chain->chain_type, HINIC_API_CMD_STATUS_GET(val, CPLD_ERR),
		HINIC_API_CMD_STATUS_GET(val, CHKSUM_ERR),
		HINIC_API_CMD_STATUS_GET(val, FSM));

	dev_err(&chain->hwअगर->pdev->dev, "Chain hw current ci: 0x%x\n",
		HINIC_API_CMD_STATUS_GET(val, CONS_IDX));

	addr = HINIC_CSR_API_CMD_CHAIN_PI_ADDR(chain->chain_type);
	val  = hinic_hwअगर_पढ़ो_reg(chain->hwअगर, addr);
	dev_err(&chain->hwअगर->pdev->dev, "Chain hw current pi: 0x%x\n", val);
पूर्ण

/**
 * chain_busy - check अगर the chain is still processing last requests
 * @chain: chain to check
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक chain_busy(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u32 prod_idx;

	चयन (chain->chain_type) अणु
	हाल HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		chain->cons_idx = get_hw_cons_idx(chain);
		prod_idx = chain->prod_idx;

		/* check क्रम a space क्रम a new command */
		अगर (chain->cons_idx == MASKED_IDX(chain, prod_idx + 1)) अणु
			dev_err(&pdev->dev, "API CMD chain %d is busy, cons_idx: %d, prod_idx: %d\n",
				chain->chain_type, chain->cons_idx,
				chain->prod_idx);
			dump_api_chain_reg(chain);
			वापस -EBUSY;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "Unknown API CMD Chain type\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * get_cell_data_size - get the data size of a specअगरic cell type
 * @type: chain type
 *
 * Return the data(Desc + Address) size in the cell
 **/
अटल u8 get_cell_data_size(क्रमागत hinic_api_cmd_chain_type type)
अणु
	u8 cell_data_size = 0;

	चयन (type) अणु
	हाल HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		cell_data_size = ALIGN(API_CMD_CELL_DESC_SIZE +
				       API_CMD_CELL_DATA_ADDR_SIZE,
				       API_CMD_CELL_ALIGNMENT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस cell_data_size;
पूर्ण

/**
 * prepare_cell_ctrl - prepare the ctrl of the cell क्रम the command
 * @cell_ctrl: the control of the cell to set the control value पूर्णांकo it
 * @data_size: the size of the data in the cell
 **/
अटल व्योम prepare_cell_ctrl(u64 *cell_ctrl, u16 data_size)
अणु
	u8 chksum;
	u64 ctrl;

	ctrl =  HINIC_API_CMD_CELL_CTRL_SET(SIZE_8BYTES(data_size), DATA_SZ)  |
		HINIC_API_CMD_CELL_CTRL_SET(RD_DMA_ATTR_DEFAULT, RD_DMA_ATTR) |
		HINIC_API_CMD_CELL_CTRL_SET(WR_DMA_ATTR_DEFAULT, WR_DMA_ATTR);

	chksum = xor_chksum_set(&ctrl);

	ctrl |= HINIC_API_CMD_CELL_CTRL_SET(chksum, XOR_CHKSUM);

	/* The data in the HW should be in Big Endian Format */
	*cell_ctrl = cpu_to_be64(ctrl);
पूर्ण

/**
 * prepare_api_cmd - prepare API CMD command
 * @chain: chain क्रम the command
 * @dest: destination node on the card that will receive the command
 * @cmd: command data
 * @cmd_size: the command size
 **/
अटल व्योम prepare_api_cmd(काष्ठा hinic_api_cmd_chain *chain,
			    क्रमागत hinic_node_id dest,
			    व्योम *cmd, u16 cmd_size)
अणु
	काष्ठा hinic_api_cmd_cell *cell = chain->curr_node;
	काष्ठा hinic_api_cmd_cell_ctxt *cell_ctxt;
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	cell_ctxt = &chain->cell_ctxt[chain->prod_idx];

	चयन (chain->chain_type) अणु
	हाल HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		cell->desc = HINIC_API_CMD_DESC_SET(SGE_DATA, API_TYPE)   |
			     HINIC_API_CMD_DESC_SET(API_CMD_WRITE, RD_WR) |
			     HINIC_API_CMD_DESC_SET(NO_BYPASS, MGMT_BYPASS);
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "unknown Chain type\n");
		वापस;
	पूर्ण

	cell->desc |= HINIC_API_CMD_DESC_SET(dest, DEST)        |
		      HINIC_API_CMD_DESC_SET(SIZE_4BYTES(cmd_size), SIZE);

	cell->desc |= HINIC_API_CMD_DESC_SET(xor_chksum_set(&cell->desc),
					     XOR_CHKSUM);

	/* The data in the HW should be in Big Endian Format */
	cell->desc = cpu_to_be64(cell->desc);

	स_नकल(cell_ctxt->api_cmd_vaddr, cmd, cmd_size);
पूर्ण

/**
 * prepare_cell - prepare cell ctrl and cmd in the current cell
 * @chain: chain क्रम the command
 * @dest: destination node on the card that will receive the command
 * @cmd: command data
 * @cmd_size: the command size
 *
 * Return 0 - Success, negative - Failure
 **/
अटल व्योम prepare_cell(काष्ठा hinic_api_cmd_chain *chain,
			 क्रमागत  hinic_node_id dest,
			 व्योम *cmd, u16 cmd_size)
अणु
	काष्ठा hinic_api_cmd_cell *curr_node = chain->curr_node;
	u16 data_size = get_cell_data_size(chain->chain_type);

	prepare_cell_ctrl(&curr_node->ctrl, data_size);
	prepare_api_cmd(chain, dest, cmd, cmd_size);
पूर्ण

अटल अंतरभूत व्योम cmd_chain_prod_idx_inc(काष्ठा hinic_api_cmd_chain *chain)
अणु
	chain->prod_idx = MASKED_IDX(chain, chain->prod_idx + 1);
पूर्ण

/**
 * api_cmd_status_update - update the status in the chain काष्ठा
 * @chain: chain to update
 **/
अटल व्योम api_cmd_status_update(काष्ठा hinic_api_cmd_chain *chain)
अणु
	क्रमागत hinic_api_cmd_chain_type chain_type;
	काष्ठा hinic_api_cmd_status *wb_status;
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u64 status_header;
	u32 status;

	wb_status = chain->wb_status;
	status_header = be64_to_cpu(wb_status->header);

	status = be32_to_cpu(wb_status->status);
	अगर (HINIC_API_CMD_STATUS_GET(status, CHKSUM_ERR)) अणु
		dev_err(&pdev->dev, "API CMD status: Xor check error\n");
		वापस;
	पूर्ण

	chain_type = HINIC_API_CMD_STATUS_HEADER_GET(status_header, CHAIN_ID);
	अगर (chain_type >= HINIC_API_CMD_MAX) अणु
		dev_err(&pdev->dev, "unknown API CMD Chain %d\n", chain_type);
		वापस;
	पूर्ण

	chain->cons_idx = HINIC_API_CMD_STATUS_GET(status, CONS_IDX);
पूर्ण

/**
 * रुको_क्रम_status_poll - रुको क्रम ग_लिखो to api cmd command to complete
 * @chain: the chain of the command
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक रुको_क्रम_status_poll(काष्ठा hinic_api_cmd_chain *chain)
अणु
	पूर्णांक err = -ETIMEDOUT;
	अचिन्हित दीर्घ end;

	end = jअगरfies + msecs_to_jअगरfies(API_CMD_TIMEOUT);
	करो अणु
		api_cmd_status_update(chain);

		/* रुको क्रम CI to be updated - sign क्रम completion */
		अगर (chain->cons_idx == chain->prod_idx) अणु
			err = 0;
			अवरोध;
		पूर्ण

		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	वापस err;
पूर्ण

/**
 * रुको_क्रम_api_cmd_completion - रुको क्रम command to complete
 * @chain: chain क्रम the command
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक रुको_क्रम_api_cmd_completion(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	चयन (chain->chain_type) अणु
	हाल HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		err = रुको_क्रम_status_poll(chain);
		अगर (err) अणु
			dev_err(&pdev->dev, "API CMD Poll status timeout\n");
			dump_api_chain_reg(chain);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "unknown API CMD Chain type\n");
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * api_cmd - API CMD command
 * @chain: chain क्रम the command
 * @dest: destination node on the card that will receive the command
 * @cmd: command data
 * @cmd_size: the command size
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक api_cmd(काष्ठा hinic_api_cmd_chain *chain,
		   क्रमागत hinic_node_id dest, u8 *cmd, u16 cmd_size)
अणु
	काष्ठा hinic_api_cmd_cell_ctxt *ctxt;
	पूर्णांक err;

	करोwn(&chain->sem);
	अगर (chain_busy(chain)) अणु
		up(&chain->sem);
		वापस -EBUSY;
	पूर्ण

	prepare_cell(chain, dest, cmd, cmd_size);
	cmd_chain_prod_idx_inc(chain);

	wmb();  /* inc pi beक्रमe issue the command */

	set_prod_idx(chain);    /* issue the command */

	ctxt = &chain->cell_ctxt[chain->prod_idx];

	chain->curr_node = ctxt->cell_vaddr;

	err = रुको_क्रम_api_cmd_completion(chain);

	up(&chain->sem);
	वापस err;
पूर्ण

/**
 * hinic_api_cmd_ग_लिखो - Write API CMD command
 * @chain: chain क्रम ग_लिखो command
 * @dest: destination node on the card that will receive the command
 * @cmd: command data
 * @size: the command size
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_api_cmd_ग_लिखो(काष्ठा hinic_api_cmd_chain *chain,
			क्रमागत hinic_node_id dest, u8 *cmd, u16 size)
अणु
	/* Verअगरy the chain type */
	अगर (chain->chain_type == HINIC_API_CMD_WRITE_TO_MGMT_CPU)
		वापस api_cmd(chain, dest, cmd, size);

	वापस -EINVAL;
पूर्ण

/**
 * api_cmd_hw_restart - restart the chain in the HW
 * @chain: the API CMD specअगरic chain to restart
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक api_cmd_hw_restart(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	पूर्णांक err = -ETIMEDOUT;
	अचिन्हित दीर्घ end;
	u32 reg_addr, val;

	/* Read Modअगरy Write */
	reg_addr = HINIC_CSR_API_CMD_CHAIN_REQ_ADDR(chain->chain_type);
	val = hinic_hwअगर_पढ़ो_reg(hwअगर, reg_addr);

	val = HINIC_API_CMD_CHAIN_REQ_CLEAR(val, RESTART);
	val |= HINIC_API_CMD_CHAIN_REQ_SET(1, RESTART);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, reg_addr, val);

	end = jअगरfies + msecs_to_jअगरfies(API_CMD_TIMEOUT);
	करो अणु
		val = hinic_hwअगर_पढ़ो_reg(hwअगर, reg_addr);

		अगर (!HINIC_API_CMD_CHAIN_REQ_GET(val, RESTART)) अणु
			err = 0;
			अवरोध;
		पूर्ण

		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	वापस err;
पूर्ण

/**
 * api_cmd_ctrl_init - set the control रेजिस्टर of a chain
 * @chain: the API CMD specअगरic chain to set control रेजिस्टर क्रम
 **/
अटल व्योम api_cmd_ctrl_init(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	u32 addr, ctrl;
	u16 cell_size;

	/* Read Modअगरy Write */
	addr = HINIC_CSR_API_CMD_CHAIN_CTRL_ADDR(chain->chain_type);

	cell_size = API_CMD_CELL_SIZE_VAL(chain->cell_size);

	ctrl = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	ctrl =  HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, RESTART_WB_STAT) &
		HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, XOR_ERR)         &
		HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, AEQE_EN)         &
		HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, XOR_CHK_EN)      &
		HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, CELL_SIZE);

	ctrl |= HINIC_API_CMD_CHAIN_CTRL_SET(1, XOR_ERR)              |
		HINIC_API_CMD_CHAIN_CTRL_SET(XOR_CHK_ALL, XOR_CHK_EN) |
		HINIC_API_CMD_CHAIN_CTRL_SET(cell_size, CELL_SIZE);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, ctrl);
पूर्ण

/**
 * api_cmd_set_status_addr - set the status address of a chain in the HW
 * @chain: the API CMD specअगरic chain to set in HW status address क्रम
 **/
अटल व्योम api_cmd_set_status_addr(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	u32 addr, val;

	addr = HINIC_CSR_API_CMD_STATUS_HI_ADDR(chain->chain_type);
	val = upper_32_bits(chain->wb_status_paddr);
	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);

	addr = HINIC_CSR_API_CMD_STATUS_LO_ADDR(chain->chain_type);
	val = lower_32_bits(chain->wb_status_paddr);
	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);
पूर्ण

/**
 * api_cmd_set_num_cells - set the number cells of a chain in the HW
 * @chain: the API CMD specअगरic chain to set in HW the number of cells क्रम
 **/
अटल व्योम api_cmd_set_num_cells(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	u32 addr, val;

	addr = HINIC_CSR_API_CMD_CHAIN_NUM_CELLS_ADDR(chain->chain_type);
	val  = chain->num_cells;
	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);
पूर्ण

/**
 * api_cmd_head_init - set the head of a chain in the HW
 * @chain: the API CMD specअगरic chain to set in HW the head क्रम
 **/
अटल व्योम api_cmd_head_init(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	u32 addr, val;

	addr = HINIC_CSR_API_CMD_CHAIN_HEAD_HI_ADDR(chain->chain_type);
	val = upper_32_bits(chain->head_cell_paddr);
	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);

	addr = HINIC_CSR_API_CMD_CHAIN_HEAD_LO_ADDR(chain->chain_type);
	val = lower_32_bits(chain->head_cell_paddr);
	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);
पूर्ण

/**
 * api_cmd_chain_hw_clean - clean the HW
 * @chain: the API CMD specअगरic chain
 **/
अटल व्योम api_cmd_chain_hw_clean(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	u32 addr, ctrl;

	addr = HINIC_CSR_API_CMD_CHAIN_CTRL_ADDR(chain->chain_type);

	ctrl = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);
	ctrl = HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, RESTART_WB_STAT) &
	       HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, XOR_ERR)         &
	       HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, AEQE_EN)         &
	       HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, XOR_CHK_EN)      &
	       HINIC_API_CMD_CHAIN_CTRL_CLEAR(ctrl, CELL_SIZE);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, ctrl);
पूर्ण

/**
 * api_cmd_chain_hw_init - initialize the chain in the HW
 * @chain: the API CMD specअगरic chain to initialize in HW
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक api_cmd_chain_hw_init(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	api_cmd_chain_hw_clean(chain);

	api_cmd_set_status_addr(chain);

	err = api_cmd_hw_restart(chain);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to restart API CMD HW\n");
		वापस err;
	पूर्ण

	api_cmd_ctrl_init(chain);
	api_cmd_set_num_cells(chain);
	api_cmd_head_init(chain);
	वापस 0;
पूर्ण

/**
 * मुक्त_cmd_buf - मुक्त the dma buffer of API CMD command
 * @chain: the API CMD specअगरic chain of the cmd
 * @cell_idx: the cell index of the cmd
 **/
अटल व्योम मुक्त_cmd_buf(काष्ठा hinic_api_cmd_chain *chain, पूर्णांक cell_idx)
अणु
	काष्ठा hinic_api_cmd_cell_ctxt *cell_ctxt;
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	cell_ctxt = &chain->cell_ctxt[cell_idx];

	dma_मुक्त_coherent(&pdev->dev, API_CMD_BUF_SIZE,
			  cell_ctxt->api_cmd_vaddr,
			  cell_ctxt->api_cmd_paddr);
पूर्ण

/**
 * alloc_cmd_buf - allocate a dma buffer क्रम API CMD command
 * @chain: the API CMD specअगरic chain क्रम the cmd
 * @cell: the cell in the HW क्रम the cmd
 * @cell_idx: the index of the cell
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक alloc_cmd_buf(काष्ठा hinic_api_cmd_chain *chain,
			 काष्ठा hinic_api_cmd_cell *cell, पूर्णांक cell_idx)
अणु
	काष्ठा hinic_api_cmd_cell_ctxt *cell_ctxt;
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	dma_addr_t cmd_paddr;
	u8 *cmd_vaddr;
	पूर्णांक err = 0;

	cmd_vaddr = dma_alloc_coherent(&pdev->dev, API_CMD_BUF_SIZE,
				       &cmd_paddr, GFP_KERNEL);
	अगर (!cmd_vaddr)
		वापस -ENOMEM;

	cell_ctxt = &chain->cell_ctxt[cell_idx];

	cell_ctxt->api_cmd_vaddr = cmd_vaddr;
	cell_ctxt->api_cmd_paddr = cmd_paddr;

	/* set the cmd DMA address in the cell */
	चयन (chain->chain_type) अणु
	हाल HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		/* The data in the HW should be in Big Endian Format */
		cell->ग_लिखो.hw_cmd_paddr = cpu_to_be64(cmd_paddr);
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "Unsupported API CMD chain type\n");
		मुक्त_cmd_buf(chain, cell_idx);
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * api_cmd_create_cell - create API CMD cell क्रम specअगरic chain
 * @chain: the API CMD specअगरic chain to create its cell
 * @cell_idx: the index of the cell to create
 * @pre_node: previous cell
 * @node_vaddr: the वापसed virt addr of the cell
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक api_cmd_create_cell(काष्ठा hinic_api_cmd_chain *chain,
			       पूर्णांक cell_idx,
			       काष्ठा hinic_api_cmd_cell *pre_node,
			       काष्ठा hinic_api_cmd_cell **node_vaddr)
अणु
	काष्ठा hinic_api_cmd_cell_ctxt *cell_ctxt;
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_api_cmd_cell *node;
	dma_addr_t node_paddr;
	पूर्णांक err;

	node = dma_alloc_coherent(&pdev->dev, chain->cell_size, &node_paddr,
				  GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	node->पढ़ो.hw_wb_resp_paddr = 0;

	cell_ctxt = &chain->cell_ctxt[cell_idx];
	cell_ctxt->cell_vaddr = node;
	cell_ctxt->cell_paddr = node_paddr;

	अगर (!pre_node) अणु
		chain->head_cell_paddr = node_paddr;
		chain->head_node = node;
	पूर्ण अन्यथा अणु
		/* The data in the HW should be in Big Endian Format */
		pre_node->next_cell_paddr = cpu_to_be64(node_paddr);
	पूर्ण

	चयन (chain->chain_type) अणु
	हाल HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		err = alloc_cmd_buf(chain, node, cell_idx);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to allocate cmd buffer\n");
			जाओ err_alloc_cmd_buf;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "Unsupported API CMD chain type\n");
		err = -EINVAL;
		जाओ err_alloc_cmd_buf;
	पूर्ण

	*node_vaddr = node;
	वापस 0;

err_alloc_cmd_buf:
	dma_मुक्त_coherent(&pdev->dev, chain->cell_size, node, node_paddr);
	वापस err;
पूर्ण

/**
 * api_cmd_destroy_cell - destroy API CMD cell of specअगरic chain
 * @chain: the API CMD specअगरic chain to destroy its cell
 * @cell_idx: the cell to destroy
 **/
अटल व्योम api_cmd_destroy_cell(काष्ठा hinic_api_cmd_chain *chain,
				 पूर्णांक cell_idx)
अणु
	काष्ठा hinic_api_cmd_cell_ctxt *cell_ctxt;
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_api_cmd_cell *node;
	dma_addr_t node_paddr;
	माप_प्रकार node_size;

	cell_ctxt = &chain->cell_ctxt[cell_idx];

	node = cell_ctxt->cell_vaddr;
	node_paddr = cell_ctxt->cell_paddr;
	node_size = chain->cell_size;

	अगर (cell_ctxt->api_cmd_vaddr) अणु
		चयन (chain->chain_type) अणु
		हाल HINIC_API_CMD_WRITE_TO_MGMT_CPU:
			मुक्त_cmd_buf(chain, cell_idx);
			अवरोध;
		शेष:
			dev_err(&pdev->dev, "Unsupported API CMD chain type\n");
			अवरोध;
		पूर्ण

		dma_मुक्त_coherent(&pdev->dev, node_size, node,
				  node_paddr);
	पूर्ण
पूर्ण

/**
 * api_cmd_destroy_cells - destroy API CMD cells of specअगरic chain
 * @chain: the API CMD specअगरic chain to destroy its cells
 * @num_cells: number of cells to destroy
 **/
अटल व्योम api_cmd_destroy_cells(काष्ठा hinic_api_cmd_chain *chain,
				  पूर्णांक num_cells)
अणु
	पूर्णांक cell_idx;

	क्रम (cell_idx = 0; cell_idx < num_cells; cell_idx++)
		api_cmd_destroy_cell(chain, cell_idx);
पूर्ण

/**
 * api_cmd_create_cells - create API CMD cells क्रम specअगरic chain
 * @chain: the API CMD specअगरic chain
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक api_cmd_create_cells(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_api_cmd_cell *node = शून्य, *pre_node = शून्य;
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err, cell_idx;

	क्रम (cell_idx = 0; cell_idx < chain->num_cells; cell_idx++) अणु
		err = api_cmd_create_cell(chain, cell_idx, pre_node, &node);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to create API CMD cell\n");
			जाओ err_create_cell;
		पूर्ण

		pre_node = node;
	पूर्ण

	/* set the Final node to poपूर्णांक on the start */
	node->next_cell_paddr = cpu_to_be64(chain->head_cell_paddr);

	/* set the current node to be the head */
	chain->curr_node = chain->head_node;
	वापस 0;

err_create_cell:
	api_cmd_destroy_cells(chain, cell_idx);
	वापस err;
पूर्ण

/**
 * api_chain_init - initialize API CMD specअगरic chain
 * @chain: the API CMD specअगरic chain to initialize
 * @attr: attributes to set in the chain
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक api_chain_init(काष्ठा hinic_api_cmd_chain *chain,
			  काष्ठा hinic_api_cmd_chain_attr *attr)
अणु
	काष्ठा hinic_hwअगर *hwअगर = attr->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार cell_ctxt_size;

	chain->hwअगर = hwअगर;
	chain->chain_type  = attr->chain_type;
	chain->num_cells = attr->num_cells;
	chain->cell_size = attr->cell_size;

	chain->prod_idx  = 0;
	chain->cons_idx  = 0;

	sema_init(&chain->sem, 1);

	cell_ctxt_size = chain->num_cells * माप(*chain->cell_ctxt);
	chain->cell_ctxt = devm_kzalloc(&pdev->dev, cell_ctxt_size, GFP_KERNEL);
	अगर (!chain->cell_ctxt)
		वापस -ENOMEM;

	chain->wb_status = dma_alloc_coherent(&pdev->dev,
					      माप(*chain->wb_status),
					      &chain->wb_status_paddr,
					      GFP_KERNEL);
	अगर (!chain->wb_status) अणु
		dev_err(&pdev->dev, "Failed to allocate DMA wb status\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * api_chain_मुक्त - मुक्त API CMD specअगरic chain
 * @chain: the API CMD specअगरic chain to मुक्त
 **/
अटल व्योम api_chain_मुक्त(काष्ठा hinic_api_cmd_chain *chain)
अणु
	काष्ठा hinic_hwअगर *hwअगर = chain->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	dma_मुक्त_coherent(&pdev->dev, माप(*chain->wb_status),
			  chain->wb_status, chain->wb_status_paddr);
पूर्ण

/**
 * api_cmd_create_chain - create API CMD specअगरic chain
 * @attr: attributes to set the chain
 *
 * Return the created chain
 **/
अटल काष्ठा hinic_api_cmd_chain *
	api_cmd_create_chain(काष्ठा hinic_api_cmd_chain_attr *attr)
अणु
	काष्ठा hinic_hwअगर *hwअगर = attr->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_api_cmd_chain *chain;
	पूर्णांक err;

	अगर (attr->num_cells & (attr->num_cells - 1)) अणु
		dev_err(&pdev->dev, "Invalid number of cells, must be power of 2\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	chain = devm_kzalloc(&pdev->dev, माप(*chain), GFP_KERNEL);
	अगर (!chain)
		वापस ERR_PTR(-ENOMEM);

	err = api_chain_init(chain, attr);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize chain\n");
		वापस ERR_PTR(err);
	पूर्ण

	err = api_cmd_create_cells(chain);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to create cells for API CMD chain\n");
		जाओ err_create_cells;
	पूर्ण

	err = api_cmd_chain_hw_init(chain);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize chain HW\n");
		जाओ err_chain_hw_init;
	पूर्ण

	वापस chain;

err_chain_hw_init:
	api_cmd_destroy_cells(chain, chain->num_cells);

err_create_cells:
	api_chain_मुक्त(chain);
	वापस ERR_PTR(err);
पूर्ण

/**
 * api_cmd_destroy_chain - destroy API CMD specअगरic chain
 * @chain: the API CMD specअगरic chain to destroy
 **/
अटल व्योम api_cmd_destroy_chain(काष्ठा hinic_api_cmd_chain *chain)
अणु
	api_cmd_chain_hw_clean(chain);
	api_cmd_destroy_cells(chain, chain->num_cells);
	api_chain_मुक्त(chain);
पूर्ण

/**
 * hinic_api_cmd_init - Initialize all the API CMD chains
 * @chain: the API CMD chains that are initialized
 * @hwअगर: the hardware पूर्णांकerface of a pci function device
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_api_cmd_init(काष्ठा hinic_api_cmd_chain **chain,
		       काष्ठा hinic_hwअगर *hwअगर)
अणु
	क्रमागत hinic_api_cmd_chain_type type, chain_type;
	काष्ठा hinic_api_cmd_chain_attr attr;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार hw_cell_sz;
	पूर्णांक err;

	hw_cell_sz = माप(काष्ठा hinic_api_cmd_cell);

	attr.hwअगर = hwअगर;
	attr.num_cells  = API_CHAIN_NUM_CELLS;
	attr.cell_size  = API_CMD_CELL_SIZE(hw_cell_sz);

	chain_type = HINIC_API_CMD_WRITE_TO_MGMT_CPU;
	क्रम ( ; chain_type < HINIC_API_CMD_MAX; chain_type++) अणु
		attr.chain_type = chain_type;

		अगर (chain_type != HINIC_API_CMD_WRITE_TO_MGMT_CPU)
			जारी;

		chain[chain_type] = api_cmd_create_chain(&attr);
		अगर (IS_ERR(chain[chain_type])) अणु
			dev_err(&pdev->dev, "Failed to create chain %d\n",
				chain_type);
			err = PTR_ERR(chain[chain_type]);
			जाओ err_create_chain;
		पूर्ण
	पूर्ण

	वापस 0;

err_create_chain:
	type = HINIC_API_CMD_WRITE_TO_MGMT_CPU;
	क्रम ( ; type < chain_type; type++) अणु
		अगर (type != HINIC_API_CMD_WRITE_TO_MGMT_CPU)
			जारी;

		api_cmd_destroy_chain(chain[type]);
	पूर्ण

	वापस err;
पूर्ण

/**
 * hinic_api_cmd_मुक्त - मुक्त the API CMD chains
 * @chain: the API CMD chains that are मुक्तd
 **/
व्योम hinic_api_cmd_मुक्त(काष्ठा hinic_api_cmd_chain **chain)
अणु
	क्रमागत hinic_api_cmd_chain_type chain_type;

	chain_type = HINIC_API_CMD_WRITE_TO_MGMT_CPU;
	क्रम ( ; chain_type < HINIC_API_CMD_MAX; chain_type++) अणु
		अगर (chain_type != HINIC_API_CMD_WRITE_TO_MGMT_CPU)
			जारी;

		api_cmd_destroy_chain(chain[chain_type]);
	पूर्ण
पूर्ण
