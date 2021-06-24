<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IBM Hot Plug Controller Driver
 *
 * Written By: Jyoti Shah, IBM Corporation
 *
 * Copyright (C) 2001-2003 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <gregkh@us.ibm.com>
 *                  <jshah@us.ibm.com>
 *
 */

#समावेश <linux/रुको.h>
#समावेश <linux/समय.स>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश "ibmphp.h"

अटल पूर्णांक to_debug = 0;
#घोषणा debug_polling(fmt, arg...)	करो अणु अगर (to_debug) debug(fmt, arg); पूर्ण जबतक (0)

//----------------------------------------------------------------------------
// समयout values
//----------------------------------------------------------------------------
#घोषणा CMD_COMPLETE_TOUT_SEC	60	// give HPC 60 sec to finish cmd
#घोषणा HPC_CTLR_WORKING_TOUT	60	// give HPC 60 sec to finish cmd
#घोषणा HPC_GETACCESS_TIMEOUT	60	// seconds
#घोषणा POLL_INTERVAL_SEC	2	// poll HPC every 2 seconds
#घोषणा POLL_LATCH_CNT		5	// poll latch 5 बार, then poll slots

//----------------------------------------------------------------------------
// Winnipeg Architected Register Offsets
//----------------------------------------------------------------------------
#घोषणा WPG_I2CMBUFL_OFFSET	0x08	// I2C Message Buffer Low
#घोषणा WPG_I2CMOSUP_OFFSET	0x10	// I2C Master Operation Setup Reg
#घोषणा WPG_I2CMCNTL_OFFSET	0x20	// I2C Master Control Register
#घोषणा WPG_I2CPARM_OFFSET	0x40	// I2C Parameter Register
#घोषणा WPG_I2CSTAT_OFFSET	0x70	// I2C Status Register

//----------------------------------------------------------------------------
// Winnipeg Store Type commands (Add this commands to the रेजिस्टर offset)
//----------------------------------------------------------------------------
#घोषणा WPG_I2C_AND		0x1000	// I2C AND operation
#घोषणा WPG_I2C_OR		0x2000	// I2C OR operation

//----------------------------------------------------------------------------
// Command set क्रम I2C Master Operation Setup Register
//----------------------------------------------------------------------------
#घोषणा WPG_READATADDR_MASK	0x00010000	// पढ़ो,bytes,I2C shअगरted,index
#घोषणा WPG_WRITEATADDR_MASK	0x40010000	// ग_लिखो,bytes,I2C shअगरted,index
#घोषणा WPG_READसूचीECT_MASK	0x10010000
#घोषणा WPG_WRITEसूचीECT_MASK	0x60010000


//----------------------------------------------------------------------------
// bit masks क्रम I2C Master Control Register
//----------------------------------------------------------------------------
#घोषणा WPG_I2CMCNTL_STARTOP_MASK	0x00000002	// Start the Operation

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
#घोषणा WPG_I2C_IOREMAP_SIZE	0x2044	// size of linear address पूर्णांकerval

//----------------------------------------------------------------------------
// command index
//----------------------------------------------------------------------------
#घोषणा WPG_1ST_SLOT_INDEX	0x01	// index - 1st slot क्रम ctlr
#घोषणा WPG_CTLR_INDEX		0x0F	// index - ctlr
#घोषणा WPG_1ST_EXTSLOT_INDEX	0x10	// index - 1st ext slot क्रम ctlr
#घोषणा WPG_1ST_BUS_INDEX	0x1F	// index - 1st bus क्रम ctlr

//----------------------------------------------------------------------------
// macro utilities
//----------------------------------------------------------------------------
// अगर bits 20,22,25,26,27,29,30 are OFF वापस 1
#घोषणा HPC_I2CSTATUS_CHECK(s)	((u8)((s & 0x00000A76) ? 0 : 1))

//----------------------------------------------------------------------------
// global variables
//----------------------------------------------------------------------------
अटल DEFINE_MUTEX(sem_hpcaccess);	// lock access to HPC
अटल DEFINE_MUTEX(operations_mutex);	// lock all operations and
					// access to data काष्ठाures
अटल DECLARE_COMPLETION(निकास_complete); // make sure polling thपढ़ो goes away
अटल काष्ठा task_काष्ठा *ibmphp_poll_thपढ़ो;
//----------------------------------------------------------------------------
// local function prototypes
//----------------------------------------------------------------------------
अटल u8 i2c_ctrl_पढ़ो(काष्ठा controller *, व्योम __iomem *, u8);
अटल u8 i2c_ctrl_ग_लिखो(काष्ठा controller *, व्योम __iomem *, u8, u8);
अटल u8 hpc_ग_लिखोcmdtoindex(u8, u8);
अटल u8 hpc_पढ़ोcmdtoindex(u8, u8);
अटल व्योम get_hpc_access(व्योम);
अटल व्योम मुक्त_hpc_access(व्योम);
अटल पूर्णांक poll_hpc(व्योम *data);
अटल पूर्णांक process_changeinstatus(काष्ठा slot *, काष्ठा slot *);
अटल पूर्णांक process_changeinlatch(u8, u8, काष्ठा controller *);
अटल पूर्णांक hpc_रुको_ctlr_notworking(पूर्णांक, काष्ठा controller *, व्योम __iomem *, u8 *);
//----------------------------------------------------------------------------


/*----------------------------------------------------------------------
* Name:    i2c_ctrl_पढ़ो
*
* Action:  पढ़ो from HPC over I2C
*
*---------------------------------------------------------------------*/
अटल u8 i2c_ctrl_पढ़ो(काष्ठा controller *ctlr_ptr, व्योम __iomem *WPGBbar, u8 index)
अणु
	u8 status;
	पूर्णांक i;
	व्योम __iomem *wpg_addr;	// base addr + offset
	अचिन्हित दीर्घ wpg_data;	// data to/from WPG LOHI क्रमmat
	अचिन्हित दीर्घ ultemp;
	अचिन्हित दीर्घ data;	// actual data HILO क्रमmat

	debug_polling("%s - Entry WPGBbar[%p] index[%x] \n", __func__, WPGBbar, index);

	//--------------------------------------------------------------------
	// READ - step 1
	// पढ़ो at address, byte length, I2C address (shअगरted), index
	// or पढ़ो direct, byte length, index
	अगर (ctlr_ptr->ctlr_type == 0x02) अणु
		data = WPG_READATADDR_MASK;
		// fill in I2C address
		ultemp = (अचिन्हित दीर्घ)ctlr_ptr->u.wpeg_ctlr.i2c_addr;
		ultemp = ultemp >> 1;
		data |= (ultemp << 8);

		// fill in index
		data |= (अचिन्हित दीर्घ)index;
	पूर्ण अन्यथा अगर (ctlr_ptr->ctlr_type == 0x04) अणु
		data = WPG_READसूचीECT_MASK;

		// fill in index
		ultemp = (अचिन्हित दीर्घ)index;
		ultemp = ultemp << 8;
		data |= ultemp;
	पूर्ण अन्यथा अणु
		err("this controller type is not supported \n");
		वापस HPC_ERROR;
	पूर्ण

	wpg_data = swab32(data);	// swap data beक्रमe writing
	wpg_addr = WPGBbar + WPG_I2CMOSUP_OFFSET;
	ग_लिखोl(wpg_data, wpg_addr);

	//--------------------------------------------------------------------
	// READ - step 2 : clear the message buffer
	data = 0x00000000;
	wpg_data = swab32(data);
	wpg_addr = WPGBbar + WPG_I2CMBUFL_OFFSET;
	ग_लिखोl(wpg_data, wpg_addr);

	//--------------------------------------------------------------------
	// READ - step 3 : issue start operation, I2C master control bit 30:ON
	//                 2020 : [20] OR operation at [20] offset 0x20
	data = WPG_I2CMCNTL_STARTOP_MASK;
	wpg_data = swab32(data);
	wpg_addr = WPGBbar + WPG_I2CMCNTL_OFFSET + WPG_I2C_OR;
	ग_लिखोl(wpg_data, wpg_addr);

	//--------------------------------------------------------------------
	// READ - step 4 : रुको until start operation bit clears
	i = CMD_COMPLETE_TOUT_SEC;
	जबतक (i) अणु
		msleep(10);
		wpg_addr = WPGBbar + WPG_I2CMCNTL_OFFSET;
		wpg_data = पढ़ोl(wpg_addr);
		data = swab32(wpg_data);
		अगर (!(data & WPG_I2CMCNTL_STARTOP_MASK))
			अवरोध;
		i--;
	पूर्ण
	अगर (i == 0) अणु
		debug("%s - Error : WPG timeout\n", __func__);
		वापस HPC_ERROR;
	पूर्ण
	//--------------------------------------------------------------------
	// READ - step 5 : पढ़ो I2C status रेजिस्टर
	i = CMD_COMPLETE_TOUT_SEC;
	जबतक (i) अणु
		msleep(10);
		wpg_addr = WPGBbar + WPG_I2CSTAT_OFFSET;
		wpg_data = पढ़ोl(wpg_addr);
		data = swab32(wpg_data);
		अगर (HPC_I2CSTATUS_CHECK(data))
			अवरोध;
		i--;
	पूर्ण
	अगर (i == 0) अणु
		debug("ctrl_read - Exit Error:I2C timeout\n");
		वापस HPC_ERROR;
	पूर्ण

	//--------------------------------------------------------------------
	// READ - step 6 : get DATA
	wpg_addr = WPGBbar + WPG_I2CMBUFL_OFFSET;
	wpg_data = पढ़ोl(wpg_addr);
	data = swab32(wpg_data);

	status = (u8) data;

	debug_polling("%s - Exit index[%x] status[%x]\n", __func__, index, status);

	वापस (status);
पूर्ण

/*----------------------------------------------------------------------
* Name:    i2c_ctrl_ग_लिखो
*
* Action:  ग_लिखो to HPC over I2C
*
* Return   0 or error codes
*---------------------------------------------------------------------*/
अटल u8 i2c_ctrl_ग_लिखो(काष्ठा controller *ctlr_ptr, व्योम __iomem *WPGBbar, u8 index, u8 cmd)
अणु
	u8 rc;
	व्योम __iomem *wpg_addr;	// base addr + offset
	अचिन्हित दीर्घ wpg_data;	// data to/from WPG LOHI क्रमmat
	अचिन्हित दीर्घ ultemp;
	अचिन्हित दीर्घ data;	// actual data HILO क्रमmat
	पूर्णांक i;

	debug_polling("%s - Entry WPGBbar[%p] index[%x] cmd[%x]\n", __func__, WPGBbar, index, cmd);

	rc = 0;
	//--------------------------------------------------------------------
	// WRITE - step 1
	// ग_लिखो at address, byte length, I2C address (shअगरted), index
	// or ग_लिखो direct, byte length, index
	data = 0x00000000;

	अगर (ctlr_ptr->ctlr_type == 0x02) अणु
		data = WPG_WRITEATADDR_MASK;
		// fill in I2C address
		ultemp = (अचिन्हित दीर्घ)ctlr_ptr->u.wpeg_ctlr.i2c_addr;
		ultemp = ultemp >> 1;
		data |= (ultemp << 8);

		// fill in index
		data |= (अचिन्हित दीर्घ)index;
	पूर्ण अन्यथा अगर (ctlr_ptr->ctlr_type == 0x04) अणु
		data = WPG_WRITEसूचीECT_MASK;

		// fill in index
		ultemp = (अचिन्हित दीर्घ)index;
		ultemp = ultemp << 8;
		data |= ultemp;
	पूर्ण अन्यथा अणु
		err("this controller type is not supported \n");
		वापस HPC_ERROR;
	पूर्ण

	wpg_data = swab32(data);	// swap data beक्रमe writing
	wpg_addr = WPGBbar + WPG_I2CMOSUP_OFFSET;
	ग_लिखोl(wpg_data, wpg_addr);

	//--------------------------------------------------------------------
	// WRITE - step 2 : clear the message buffer
	data = 0x00000000 | (अचिन्हित दीर्घ)cmd;
	wpg_data = swab32(data);
	wpg_addr = WPGBbar + WPG_I2CMBUFL_OFFSET;
	ग_लिखोl(wpg_data, wpg_addr);

	//--------------------------------------------------------------------
	// WRITE - step 3 : issue start operation,I2C master control bit 30:ON
	//                 2020 : [20] OR operation at [20] offset 0x20
	data = WPG_I2CMCNTL_STARTOP_MASK;
	wpg_data = swab32(data);
	wpg_addr = WPGBbar + WPG_I2CMCNTL_OFFSET + WPG_I2C_OR;
	ग_लिखोl(wpg_data, wpg_addr);

	//--------------------------------------------------------------------
	// WRITE - step 4 : रुको until start operation bit clears
	i = CMD_COMPLETE_TOUT_SEC;
	जबतक (i) अणु
		msleep(10);
		wpg_addr = WPGBbar + WPG_I2CMCNTL_OFFSET;
		wpg_data = पढ़ोl(wpg_addr);
		data = swab32(wpg_data);
		अगर (!(data & WPG_I2CMCNTL_STARTOP_MASK))
			अवरोध;
		i--;
	पूर्ण
	अगर (i == 0) अणु
		debug("%s - Exit Error:WPG timeout\n", __func__);
		rc = HPC_ERROR;
	पूर्ण

	//--------------------------------------------------------------------
	// WRITE - step 5 : पढ़ो I2C status रेजिस्टर
	i = CMD_COMPLETE_TOUT_SEC;
	जबतक (i) अणु
		msleep(10);
		wpg_addr = WPGBbar + WPG_I2CSTAT_OFFSET;
		wpg_data = पढ़ोl(wpg_addr);
		data = swab32(wpg_data);
		अगर (HPC_I2CSTATUS_CHECK(data))
			अवरोध;
		i--;
	पूर्ण
	अगर (i == 0) अणु
		debug("ctrl_read - Error : I2C timeout\n");
		rc = HPC_ERROR;
	पूर्ण

	debug_polling("%s Exit rc[%x]\n", __func__, rc);
	वापस (rc);
पूर्ण

//------------------------------------------------------------
//  Read from ISA type HPC
//------------------------------------------------------------
अटल u8 isa_ctrl_पढ़ो(काष्ठा controller *ctlr_ptr, u8 offset)
अणु
	u16 start_address;
	u16 end_address;
	u8 data;

	start_address = ctlr_ptr->u.isa_ctlr.io_start;
	end_address = ctlr_ptr->u.isa_ctlr.io_end;
	data = inb(start_address + offset);
	वापस data;
पूर्ण

//--------------------------------------------------------------
// Write to ISA type HPC
//--------------------------------------------------------------
अटल व्योम isa_ctrl_ग_लिखो(काष्ठा controller *ctlr_ptr, u8 offset, u8 data)
अणु
	u16 start_address;
	u16 port_address;

	start_address = ctlr_ptr->u.isa_ctlr.io_start;
	port_address = start_address + (u16) offset;
	outb(data, port_address);
पूर्ण

अटल u8 pci_ctrl_पढ़ो(काष्ठा controller *ctrl, u8 offset)
अणु
	u8 data = 0x00;
	debug("inside pci_ctrl_read\n");
	अगर (ctrl->ctrl_dev)
		pci_पढ़ो_config_byte(ctrl->ctrl_dev, HPC_PCI_OFFSET + offset, &data);
	वापस data;
पूर्ण

अटल u8 pci_ctrl_ग_लिखो(काष्ठा controller *ctrl, u8 offset, u8 data)
अणु
	u8 rc = -ENODEV;
	debug("inside pci_ctrl_write\n");
	अगर (ctrl->ctrl_dev) अणु
		pci_ग_लिखो_config_byte(ctrl->ctrl_dev, HPC_PCI_OFFSET + offset, data);
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

अटल u8 ctrl_पढ़ो(काष्ठा controller *ctlr, व्योम __iomem *base, u8 offset)
अणु
	u8 rc;
	चयन (ctlr->ctlr_type) अणु
	हाल 0:
		rc = isa_ctrl_पढ़ो(ctlr, offset);
		अवरोध;
	हाल 1:
		rc = pci_ctrl_पढ़ो(ctlr, offset);
		अवरोध;
	हाल 2:
	हाल 4:
		rc = i2c_ctrl_पढ़ो(ctlr, base, offset);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस rc;
पूर्ण

अटल u8 ctrl_ग_लिखो(काष्ठा controller *ctlr, व्योम __iomem *base, u8 offset, u8 data)
अणु
	u8 rc = 0;
	चयन (ctlr->ctlr_type) अणु
	हाल 0:
		isa_ctrl_ग_लिखो(ctlr, offset, data);
		अवरोध;
	हाल 1:
		rc = pci_ctrl_ग_लिखो(ctlr, offset, data);
		अवरोध;
	हाल 2:
	हाल 4:
		rc = i2c_ctrl_ग_लिखो(ctlr, base, offset, data);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस rc;
पूर्ण
/*----------------------------------------------------------------------
* Name:    hpc_ग_लिखोcmdtoindex()
*
* Action:  convert a ग_लिखो command to proper index within a controller
*
* Return   index, HPC_ERROR
*---------------------------------------------------------------------*/
अटल u8 hpc_ग_लिखोcmdtoindex(u8 cmd, u8 index)
अणु
	u8 rc;

	चयन (cmd) अणु
	हाल HPC_CTLR_ENABLEIRQ:	// 0x00.N.15
	हाल HPC_CTLR_CLEARIRQ:	// 0x06.N.15
	हाल HPC_CTLR_RESET:	// 0x07.N.15
	हाल HPC_CTLR_IRQSTEER:	// 0x08.N.15
	हाल HPC_CTLR_DISABLEIRQ:	// 0x01.N.15
	हाल HPC_ALLSLOT_ON:	// 0x11.N.15
	हाल HPC_ALLSLOT_OFF:	// 0x12.N.15
		rc = 0x0F;
		अवरोध;

	हाल HPC_SLOT_OFF:	// 0x02.Y.0-14
	हाल HPC_SLOT_ON:	// 0x03.Y.0-14
	हाल HPC_SLOT_ATTNOFF:	// 0x04.N.0-14
	हाल HPC_SLOT_ATTNON:	// 0x05.N.0-14
	हाल HPC_SLOT_BLINKLED:	// 0x13.N.0-14
		rc = index;
		अवरोध;

	हाल HPC_BUS_33CONVMODE:
	हाल HPC_BUS_66CONVMODE:
	हाल HPC_BUS_66PCIXMODE:
	हाल HPC_BUS_100PCIXMODE:
	हाल HPC_BUS_133PCIXMODE:
		rc = index + WPG_1ST_BUS_INDEX - 1;
		अवरोध;

	शेष:
		err("hpc_writecmdtoindex - Error invalid cmd[%x]\n", cmd);
		rc = HPC_ERROR;
	पूर्ण

	वापस rc;
पूर्ण

/*----------------------------------------------------------------------
* Name:    hpc_पढ़ोcmdtoindex()
*
* Action:  convert a पढ़ो command to proper index within a controller
*
* Return   index, HPC_ERROR
*---------------------------------------------------------------------*/
अटल u8 hpc_पढ़ोcmdtoindex(u8 cmd, u8 index)
अणु
	u8 rc;

	चयन (cmd) अणु
	हाल READ_CTLRSTATUS:
		rc = 0x0F;
		अवरोध;
	हाल READ_SLOTSTATUS:
	हाल READ_ALLSTAT:
		rc = index;
		अवरोध;
	हाल READ_EXTSLOTSTATUS:
		rc = index + WPG_1ST_EXTSLOT_INDEX;
		अवरोध;
	हाल READ_BUSSTATUS:
		rc = index + WPG_1ST_BUS_INDEX - 1;
		अवरोध;
	हाल READ_SLOTLATCHLOWREG:
		rc = 0x28;
		अवरोध;
	हाल READ_REVLEVEL:
		rc = 0x25;
		अवरोध;
	हाल READ_HPCOPTIONS:
		rc = 0x27;
		अवरोध;
	शेष:
		rc = HPC_ERROR;
	पूर्ण
	वापस rc;
पूर्ण

/*----------------------------------------------------------------------
* Name:    HPCपढ़ोslot()
*
* Action:  issue a READ command to HPC
*
* Input:   pslot   - cannot be शून्य क्रम READ_ALLSTAT
*          pstatus - can be शून्य क्रम READ_ALLSTAT
*
* Return   0 or error codes
*---------------------------------------------------------------------*/
पूर्णांक ibmphp_hpc_पढ़ोslot(काष्ठा slot *pslot, u8 cmd, u8 *pstatus)
अणु
	व्योम __iomem *wpg_bbar = शून्य;
	काष्ठा controller *ctlr_ptr;
	u8 index, status;
	पूर्णांक rc = 0;
	पूर्णांक busindex;

	debug_polling("%s - Entry pslot[%p] cmd[%x] pstatus[%p]\n", __func__, pslot, cmd, pstatus);

	अगर ((pslot == शून्य)
	    || ((pstatus == शून्य) && (cmd != READ_ALLSTAT) && (cmd != READ_BUSSTATUS))) अणु
		rc = -EINVAL;
		err("%s - Error invalid pointer, rc[%d]\n", __func__, rc);
		वापस rc;
	पूर्ण

	अगर (cmd == READ_BUSSTATUS) अणु
		busindex = ibmphp_get_bus_index(pslot->bus);
		अगर (busindex < 0) अणु
			rc = -EINVAL;
			err("%s - Exit Error:invalid bus, rc[%d]\n", __func__, rc);
			वापस rc;
		पूर्ण अन्यथा
			index = (u8) busindex;
	पूर्ण अन्यथा
		index = pslot->ctlr_index;

	index = hpc_पढ़ोcmdtoindex(cmd, index);

	अगर (index == HPC_ERROR) अणु
		rc = -EINVAL;
		err("%s - Exit Error:invalid index, rc[%d]\n", __func__, rc);
		वापस rc;
	पूर्ण

	ctlr_ptr = pslot->ctrl;

	get_hpc_access();

	//--------------------------------------------------------------------
	// map physical address to logical address
	//--------------------------------------------------------------------
	अगर ((ctlr_ptr->ctlr_type == 2) || (ctlr_ptr->ctlr_type == 4))
		wpg_bbar = ioremap(ctlr_ptr->u.wpeg_ctlr.wpegbbar, WPG_I2C_IOREMAP_SIZE);

	//--------------------------------------------------------------------
	// check controller status beक्रमe पढ़ोing
	//--------------------------------------------------------------------
	rc = hpc_रुको_ctlr_notworking(HPC_CTLR_WORKING_TOUT, ctlr_ptr, wpg_bbar, &status);
	अगर (!rc) अणु
		चयन (cmd) अणु
		हाल READ_ALLSTAT:
			// update the slot काष्ठाure
			pslot->ctrl->status = status;
			pslot->status = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index);
			rc = hpc_रुको_ctlr_notworking(HPC_CTLR_WORKING_TOUT, ctlr_ptr, wpg_bbar,
						       &status);
			अगर (!rc)
				pslot->ext_status = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index + WPG_1ST_EXTSLOT_INDEX);

			अवरोध;

		हाल READ_SLOTSTATUS:
			// DO NOT update the slot काष्ठाure
			*pstatus = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index);
			अवरोध;

		हाल READ_EXTSLOTSTATUS:
			// DO NOT update the slot काष्ठाure
			*pstatus = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index);
			अवरोध;

		हाल READ_CTLRSTATUS:
			// DO NOT update the slot काष्ठाure
			*pstatus = status;
			अवरोध;

		हाल READ_BUSSTATUS:
			pslot->busstatus = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index);
			अवरोध;
		हाल READ_REVLEVEL:
			*pstatus = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index);
			अवरोध;
		हाल READ_HPCOPTIONS:
			*pstatus = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index);
			अवरोध;
		हाल READ_SLOTLATCHLOWREG:
			// DO NOT update the slot काष्ठाure
			*pstatus = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index);
			अवरोध;

			// Not used
		हाल READ_ALLSLOT:
			list_क्रम_each_entry(pslot, &ibmphp_slot_head,
					    ibm_slot_list) अणु
				index = pslot->ctlr_index;
				rc = hpc_रुको_ctlr_notworking(HPC_CTLR_WORKING_TOUT, ctlr_ptr,
								wpg_bbar, &status);
				अगर (!rc) अणु
					pslot->status = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, index);
					rc = hpc_रुको_ctlr_notworking(HPC_CTLR_WORKING_TOUT,
									ctlr_ptr, wpg_bbar, &status);
					अगर (!rc)
						pslot->ext_status =
						    ctrl_पढ़ो(ctlr_ptr, wpg_bbar,
								index + WPG_1ST_EXTSLOT_INDEX);
				पूर्ण अन्यथा अणु
					err("%s - Error ctrl_read failed\n", __func__);
					rc = -EINVAL;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	//--------------------------------------------------------------------
	// cleanup
	//--------------------------------------------------------------------

	// हटाओ physical to logical address mapping
	अगर ((ctlr_ptr->ctlr_type == 2) || (ctlr_ptr->ctlr_type == 4))
		iounmap(wpg_bbar);

	मुक्त_hpc_access();

	debug_polling("%s - Exit rc[%d]\n", __func__, rc);
	वापस rc;
पूर्ण

/*----------------------------------------------------------------------
* Name:    ibmphp_hpc_ग_लिखोslot()
*
* Action: issue a WRITE command to HPC
*---------------------------------------------------------------------*/
पूर्णांक ibmphp_hpc_ग_लिखोslot(काष्ठा slot *pslot, u8 cmd)
अणु
	व्योम __iomem *wpg_bbar = शून्य;
	काष्ठा controller *ctlr_ptr;
	u8 index, status;
	पूर्णांक busindex;
	u8 करोne;
	पूर्णांक rc = 0;
	पूर्णांक समयout;

	debug_polling("%s - Entry pslot[%p] cmd[%x]\n", __func__, pslot, cmd);
	अगर (pslot == शून्य) अणु
		rc = -EINVAL;
		err("%s - Error Exit rc[%d]\n", __func__, rc);
		वापस rc;
	पूर्ण

	अगर ((cmd == HPC_BUS_33CONVMODE) || (cmd == HPC_BUS_66CONVMODE) ||
		(cmd == HPC_BUS_66PCIXMODE) || (cmd == HPC_BUS_100PCIXMODE) ||
		(cmd == HPC_BUS_133PCIXMODE)) अणु
		busindex = ibmphp_get_bus_index(pslot->bus);
		अगर (busindex < 0) अणु
			rc = -EINVAL;
			err("%s - Exit Error:invalid bus, rc[%d]\n", __func__, rc);
			वापस rc;
		पूर्ण अन्यथा
			index = (u8) busindex;
	पूर्ण अन्यथा
		index = pslot->ctlr_index;

	index = hpc_ग_लिखोcmdtoindex(cmd, index);

	अगर (index == HPC_ERROR) अणु
		rc = -EINVAL;
		err("%s - Error Exit rc[%d]\n", __func__, rc);
		वापस rc;
	पूर्ण

	ctlr_ptr = pslot->ctrl;

	get_hpc_access();

	//--------------------------------------------------------------------
	// map physical address to logical address
	//--------------------------------------------------------------------
	अगर ((ctlr_ptr->ctlr_type == 2) || (ctlr_ptr->ctlr_type == 4)) अणु
		wpg_bbar = ioremap(ctlr_ptr->u.wpeg_ctlr.wpegbbar, WPG_I2C_IOREMAP_SIZE);

		debug("%s - ctlr id[%x] physical[%lx] logical[%lx] i2c[%x]\n", __func__,
		ctlr_ptr->ctlr_id, (uदीर्घ) (ctlr_ptr->u.wpeg_ctlr.wpegbbar), (uदीर्घ) wpg_bbar,
		ctlr_ptr->u.wpeg_ctlr.i2c_addr);
	पूर्ण
	//--------------------------------------------------------------------
	// check controller status beक्रमe writing
	//--------------------------------------------------------------------
	rc = hpc_रुको_ctlr_notworking(HPC_CTLR_WORKING_TOUT, ctlr_ptr, wpg_bbar, &status);
	अगर (!rc) अणु

		ctrl_ग_लिखो(ctlr_ptr, wpg_bbar, index, cmd);

		//--------------------------------------------------------------------
		// check controller is still not working on the command
		//--------------------------------------------------------------------
		समयout = CMD_COMPLETE_TOUT_SEC;
		करोne = 0;
		जबतक (!करोne) अणु
			rc = hpc_रुको_ctlr_notworking(HPC_CTLR_WORKING_TOUT, ctlr_ptr, wpg_bbar,
							&status);
			अगर (!rc) अणु
				अगर (NEEDTOCHECK_CMDSTATUS(cmd)) अणु
					अगर (CTLR_FINISHED(status) == HPC_CTLR_FINISHED_YES)
						करोne = 1;
				पूर्ण अन्यथा
					करोne = 1;
			पूर्ण
			अगर (!करोne) अणु
				msleep(1000);
				अगर (समयout < 1) अणु
					करोne = 1;
					err("%s - Error command complete timeout\n", __func__);
					rc = -EFAULT;
				पूर्ण अन्यथा
					समयout--;
			पूर्ण
		पूर्ण
		ctlr_ptr->status = status;
	पूर्ण
	// cleanup

	// हटाओ physical to logical address mapping
	अगर ((ctlr_ptr->ctlr_type == 2) || (ctlr_ptr->ctlr_type == 4))
		iounmap(wpg_bbar);
	मुक्त_hpc_access();

	debug_polling("%s - Exit rc[%d]\n", __func__, rc);
	वापस rc;
पूर्ण

/*----------------------------------------------------------------------
* Name:    get_hpc_access()
*
* Action: make sure only one process can access HPC at one समय
*---------------------------------------------------------------------*/
अटल व्योम get_hpc_access(व्योम)
अणु
	mutex_lock(&sem_hpcaccess);
पूर्ण

/*----------------------------------------------------------------------
* Name:    मुक्त_hpc_access()
*---------------------------------------------------------------------*/
व्योम मुक्त_hpc_access(व्योम)
अणु
	mutex_unlock(&sem_hpcaccess);
पूर्ण

/*----------------------------------------------------------------------
* Name:    ibmphp_lock_operations()
*
* Action: make sure only one process can change the data काष्ठाure
*---------------------------------------------------------------------*/
व्योम ibmphp_lock_operations(व्योम)
अणु
	mutex_lock(&operations_mutex);
	to_debug = 1;
पूर्ण

/*----------------------------------------------------------------------
* Name:    ibmphp_unlock_operations()
*---------------------------------------------------------------------*/
व्योम ibmphp_unlock_operations(व्योम)
अणु
	debug("%s - Entry\n", __func__);
	mutex_unlock(&operations_mutex);
	to_debug = 0;
	debug("%s - Exit\n", __func__);
पूर्ण

/*----------------------------------------------------------------------
* Name:    poll_hpc()
*---------------------------------------------------------------------*/
#घोषणा POLL_LATCH_REGISTER	0
#घोषणा POLL_SLOTS		1
#घोषणा POLL_SLEEP		2
अटल पूर्णांक poll_hpc(व्योम *data)
अणु
	काष्ठा slot myslot;
	काष्ठा slot *pslot = शून्य;
	पूर्णांक rc;
	पूर्णांक poll_state = POLL_LATCH_REGISTER;
	u8 oldlatchlow = 0x00;
	u8 curlatchlow = 0x00;
	पूर्णांक poll_count = 0;
	u8 ctrl_count = 0x00;

	debug("%s - Entry\n", __func__);

	जबतक (!kthपढ़ो_should_stop()) अणु
		/* try to get the lock to करो some kind of hardware access */
		mutex_lock(&operations_mutex);

		चयन (poll_state) अणु
		हाल POLL_LATCH_REGISTER:
			oldlatchlow = curlatchlow;
			ctrl_count = 0x00;
			list_क्रम_each_entry(pslot, &ibmphp_slot_head,
					    ibm_slot_list) अणु
				अगर (ctrl_count >= ibmphp_get_total_controllers())
					अवरोध;
				अगर (pslot->ctrl->ctlr_relative_id == ctrl_count) अणु
					ctrl_count++;
					अगर (READ_SLOT_LATCH(pslot->ctrl)) अणु
						rc = ibmphp_hpc_पढ़ोslot(pslot,
									  READ_SLOTLATCHLOWREG,
									  &curlatchlow);
						अगर (oldlatchlow != curlatchlow)
							process_changeinlatch(oldlatchlow,
									       curlatchlow,
									       pslot->ctrl);
					पूर्ण
				पूर्ण
			पूर्ण
			++poll_count;
			poll_state = POLL_SLEEP;
			अवरोध;
		हाल POLL_SLOTS:
			list_क्रम_each_entry(pslot, &ibmphp_slot_head,
					    ibm_slot_list) अणु
				// make a copy of the old status
				स_नकल((व्योम *) &myslot, (व्योम *) pslot,
					माप(काष्ठा slot));
				rc = ibmphp_hpc_पढ़ोslot(pslot, READ_ALLSTAT, शून्य);
				अगर ((myslot.status != pslot->status)
				    || (myslot.ext_status != pslot->ext_status))
					process_changeinstatus(pslot, &myslot);
			पूर्ण
			ctrl_count = 0x00;
			list_क्रम_each_entry(pslot, &ibmphp_slot_head,
					    ibm_slot_list) अणु
				अगर (ctrl_count >= ibmphp_get_total_controllers())
					अवरोध;
				अगर (pslot->ctrl->ctlr_relative_id == ctrl_count) अणु
					ctrl_count++;
					अगर (READ_SLOT_LATCH(pslot->ctrl))
						rc = ibmphp_hpc_पढ़ोslot(pslot,
									  READ_SLOTLATCHLOWREG,
									  &curlatchlow);
				पूर्ण
			पूर्ण
			++poll_count;
			poll_state = POLL_SLEEP;
			अवरोध;
		हाल POLL_SLEEP:
			/* करोn't sleep with a lock on the hardware */
			mutex_unlock(&operations_mutex);
			msleep(POLL_INTERVAL_SEC * 1000);

			अगर (kthपढ़ो_should_stop())
				जाओ out_sleep;

			mutex_lock(&operations_mutex);

			अगर (poll_count >= POLL_LATCH_CNT) अणु
				poll_count = 0;
				poll_state = POLL_SLOTS;
			पूर्ण अन्यथा
				poll_state = POLL_LATCH_REGISTER;
			अवरोध;
		पूर्ण
		/* give up the hardware semaphore */
		mutex_unlock(&operations_mutex);
		/* sleep क्रम a लघु समय just क्रम good measure */
out_sleep:
		msleep(100);
	पूर्ण
	complete(&निकास_complete);
	debug("%s - Exit\n", __func__);
	वापस 0;
पूर्ण


/*----------------------------------------------------------------------
* Name:    process_changeinstatus
*
* Action:  compare old and new slot status, process the change in status
*
* Input:   poपूर्णांकer to slot काष्ठा, old slot काष्ठा
*
* Return   0 or error codes
* Value:
*
* Side
* Effects: None.
*
* Notes:
*---------------------------------------------------------------------*/
अटल पूर्णांक process_changeinstatus(काष्ठा slot *pslot, काष्ठा slot *poldslot)
अणु
	u8 status;
	पूर्णांक rc = 0;
	u8 disable = 0;
	u8 update = 0;

	debug("process_changeinstatus - Entry pslot[%p], poldslot[%p]\n", pslot, poldslot);

	// bit 0 - HPC_SLOT_POWER
	अगर ((pslot->status & 0x01) != (poldslot->status & 0x01))
		update = 1;

	// bit 1 - HPC_SLOT_CONNECT
	// ignore

	// bit 2 - HPC_SLOT_ATTN
	अगर ((pslot->status & 0x04) != (poldslot->status & 0x04))
		update = 1;

	// bit 3 - HPC_SLOT_PRSNT2
	// bit 4 - HPC_SLOT_PRSNT1
	अगर (((pslot->status & 0x08) != (poldslot->status & 0x08))
		|| ((pslot->status & 0x10) != (poldslot->status & 0x10)))
		update = 1;

	// bit 5 - HPC_SLOT_PWRGD
	अगर ((pslot->status & 0x20) != (poldslot->status & 0x20))
		// OFF -> ON: ignore, ON -> OFF: disable slot
		अगर ((poldslot->status & 0x20) && (SLOT_CONNECT(poldslot->status) == HPC_SLOT_CONNECTED) && (SLOT_PRESENT(poldslot->status)))
			disable = 1;

	// bit 6 - HPC_SLOT_BUS_SPEED
	// ignore

	// bit 7 - HPC_SLOT_LATCH
	अगर ((pslot->status & 0x80) != (poldslot->status & 0x80)) अणु
		update = 1;
		// OPEN -> CLOSE
		अगर (pslot->status & 0x80) अणु
			अगर (SLOT_PWRGD(pslot->status)) अणु
				// घातer goes on and off after closing latch
				// check again to make sure घातer is still ON
				msleep(1000);
				rc = ibmphp_hpc_पढ़ोslot(pslot, READ_SLOTSTATUS, &status);
				अगर (SLOT_PWRGD(status))
					update = 1;
				अन्यथा	// overग_लिखो घातer in pslot to OFF
					pslot->status &= ~HPC_SLOT_POWER;
			पूर्ण
		पूर्ण
		// CLOSE -> OPEN
		अन्यथा अगर ((SLOT_PWRGD(poldslot->status) == HPC_SLOT_PWRGD_GOOD)
			&& (SLOT_CONNECT(poldslot->status) == HPC_SLOT_CONNECTED) && (SLOT_PRESENT(poldslot->status))) अणु
			disable = 1;
		पूर्ण
		// अन्यथा - ignore
	पूर्ण
	// bit 4 - HPC_SLOT_BLINK_ATTN
	अगर ((pslot->ext_status & 0x08) != (poldslot->ext_status & 0x08))
		update = 1;

	अगर (disable) अणु
		debug("process_changeinstatus - disable slot\n");
		pslot->flag = 0;
		rc = ibmphp_करो_disable_slot(pslot);
	पूर्ण

	अगर (update || disable)
		ibmphp_update_slot_info(pslot);

	debug("%s - Exit rc[%d] disable[%x] update[%x]\n", __func__, rc, disable, update);

	वापस rc;
पूर्ण

/*----------------------------------------------------------------------
* Name:    process_changeinlatch
*
* Action:  compare old and new latch reg status, process the change
*
* Input:   old and current latch रेजिस्टर status
*
* Return   0 or error codes
* Value:
*---------------------------------------------------------------------*/
अटल पूर्णांक process_changeinlatch(u8 old, u8 new, काष्ठा controller *ctrl)
अणु
	काष्ठा slot myslot, *pslot;
	u8 i;
	u8 mask;
	पूर्णांक rc = 0;

	debug("%s - Entry old[%x], new[%x]\n", __func__, old, new);
	// bit 0 reserved, 0 is LSB, check bit 1-6 क्रम 6 slots

	क्रम (i = ctrl->starting_slot_num; i <= ctrl->ending_slot_num; i++) अणु
		mask = 0x01 << i;
		अगर ((mask & old) != (mask & new)) अणु
			pslot = ibmphp_get_slot_from_physical_num(i);
			अगर (pslot) अणु
				स_नकल((व्योम *) &myslot, (व्योम *) pslot, माप(काष्ठा slot));
				rc = ibmphp_hpc_पढ़ोslot(pslot, READ_ALLSTAT, शून्य);
				debug("%s - call process_changeinstatus for slot[%d]\n", __func__, i);
				process_changeinstatus(pslot, &myslot);
			पूर्ण अन्यथा अणु
				rc = -EINVAL;
				err("%s - Error bad pointer for slot[%d]\n", __func__, i);
			पूर्ण
		पूर्ण
	पूर्ण
	debug("%s - Exit rc[%d]\n", __func__, rc);
	वापस rc;
पूर्ण

/*----------------------------------------------------------------------
* Name:    ibmphp_hpc_start_poll_thपढ़ो
*
* Action:  start polling thपढ़ो
*---------------------------------------------------------------------*/
पूर्णांक __init ibmphp_hpc_start_poll_thपढ़ो(व्योम)
अणु
	debug("%s - Entry\n", __func__);

	ibmphp_poll_thपढ़ो = kthपढ़ो_run(poll_hpc, शून्य, "hpc_poll");
	अगर (IS_ERR(ibmphp_poll_thपढ़ो)) अणु
		err("%s - Error, thread not started\n", __func__);
		वापस PTR_ERR(ibmphp_poll_thपढ़ो);
	पूर्ण
	वापस 0;
पूर्ण

/*----------------------------------------------------------------------
* Name:    ibmphp_hpc_stop_poll_thपढ़ो
*
* Action:  stop polling thपढ़ो and cleanup
*---------------------------------------------------------------------*/
व्योम __निकास ibmphp_hpc_stop_poll_thपढ़ो(व्योम)
अणु
	debug("%s - Entry\n", __func__);

	kthपढ़ो_stop(ibmphp_poll_thपढ़ो);
	debug("before locking operations\n");
	ibmphp_lock_operations();
	debug("after locking operations\n");

	// रुको क्रम poll thपढ़ो to निकास
	debug("before exit_complete down\n");
	रुको_क्रम_completion(&निकास_complete);
	debug("after exit_completion down\n");

	// cleanup
	debug("before free_hpc_access\n");
	मुक्त_hpc_access();
	debug("after free_hpc_access\n");
	ibmphp_unlock_operations();
	debug("after unlock operations\n");

	debug("%s - Exit\n", __func__);
पूर्ण

/*----------------------------------------------------------------------
* Name:    hpc_रुको_ctlr_notworking
*
* Action:  रुको until the controller is in a not working state
*
* Return   0, HPC_ERROR
* Value:
*---------------------------------------------------------------------*/
अटल पूर्णांक hpc_रुको_ctlr_notworking(पूर्णांक समयout, काष्ठा controller *ctlr_ptr, व्योम __iomem *wpg_bbar,
				    u8 *pstatus)
अणु
	पूर्णांक rc = 0;
	u8 करोne = 0;

	debug_polling("hpc_wait_ctlr_notworking - Entry timeout[%d]\n", समयout);

	जबतक (!करोne) अणु
		*pstatus = ctrl_पढ़ो(ctlr_ptr, wpg_bbar, WPG_CTLR_INDEX);
		अगर (*pstatus == HPC_ERROR) अणु
			rc = HPC_ERROR;
			करोne = 1;
		पूर्ण
		अगर (CTLR_WORKING(*pstatus) == HPC_CTLR_WORKING_NO)
			करोne = 1;
		अगर (!करोne) अणु
			msleep(1000);
			अगर (समयout < 1) अणु
				करोne = 1;
				err("HPCreadslot - Error ctlr timeout\n");
				rc = HPC_ERROR;
			पूर्ण अन्यथा
				समयout--;
		पूर्ण
	पूर्ण
	debug_polling("hpc_wait_ctlr_notworking - Exit rc[%x] status[%x]\n", rc, *pstatus);
	वापस rc;
पूर्ण
