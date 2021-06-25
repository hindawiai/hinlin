<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#अगर_अघोषित SYM_GLUE_H
#घोषणा SYM_GLUE_H

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>
#अगर_घोषित __sparc__
#  include <यंत्र/irq.h>
#पूर्ण_अगर

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport_spi.h>
#समावेश <scsi/scsi_host.h>

#समावेश "sym53c8xx.h"
#समावेश "sym_defs.h"
#समावेश "sym_misc.h"

/*
 * Configuration addendum क्रम Linux.
 */
#घोषणा	SYM_CONF_TIMER_INTERVAL		((HZ+1)/2)

#अघोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
#घोषणा SYM_OPT_LIMIT_COMMAND_REORDERING

/*
 *  Prपूर्णांक a message with severity.
 */
#घोषणा म_लिखो_emerg(args...)	prपूर्णांकk(KERN_EMERG args)
#घोषणा	म_लिखो_alert(args...)	prपूर्णांकk(KERN_ALERT args)
#घोषणा	म_लिखो_crit(args...)	prपूर्णांकk(KERN_CRIT args)
#घोषणा	म_लिखो_err(args...)	prपूर्णांकk(KERN_ERR	args)
#घोषणा	म_लिखो_warning(args...)	prपूर्णांकk(KERN_WARNING args)
#घोषणा	म_लिखो_notice(args...)	prपूर्णांकk(KERN_NOTICE args)
#घोषणा	म_लिखो_info(args...)	prपूर्णांकk(KERN_INFO args)
#घोषणा	म_लिखो_debug(args...)	prपूर्णांकk(KERN_DEBUG args)
#घोषणा	म_लिखो(args...)		prपूर्णांकk(args)

/*
 *  A 'read barrier' flushes any data that have been prefetched 
 *  by the processor due to out of order execution. Such a barrier 
 *  must notably be inserted prior to looking at data that have 
 *  been DMAed, assuming that program करोes memory READs in proper 
 *  order and that the device ensured proper ordering of WRITEs.
 *
 *  A 'write barrier' prevents any previous WRITEs to pass further 
 *  WRITEs. Such barriers must be inserted each समय another agent 
 *  relies on ordering of WRITEs.
 *
 *  Note that, due to posting of PCI memory ग_लिखोs, we also must 
 *  insert dummy PCI पढ़ो transactions when some ordering involving 
 *  both directions over the PCI करोes matter. PCI transactions are 
 *  fully ordered in each direction.
 */

#घोषणा MEMORY_READ_BARRIER()	rmb()
#घोषणा MEMORY_WRITE_BARRIER()	wmb()

/*
 *  IO functions definition क्रम big/little endian CPU support.
 *  For now, PCI chips are only supported in little endian addressing mode, 
 */

#अगर_घोषित	__BIG_ENDIAN

#घोषणा	पढ़ोw_l2b	पढ़ोw
#घोषणा	पढ़ोl_l2b	पढ़ोl
#घोषणा	ग_लिखोw_b2l	ग_लिखोw
#घोषणा	ग_लिखोl_b2l	ग_लिखोl

#अन्यथा	/* little endian */

#घोषणा	पढ़ोw_raw	पढ़ोw
#घोषणा	पढ़ोl_raw	पढ़ोl
#घोषणा	ग_लिखोw_raw	ग_लिखोw
#घोषणा	ग_लिखोl_raw	ग_लिखोl

#पूर्ण_अगर /* endian */

#अगर_घोषित	SYM_CONF_CHIP_BIG_ENDIAN
#त्रुटि	"Chips in BIG ENDIAN addressing mode are not (yet) supported"
#पूर्ण_अगर

/*
 *  If the CPU and the chip use same endian-ness addressing,
 *  no byte reordering is needed क्रम script patching.
 *  Macro cpu_to_scr() is to be used क्रम script patching.
 *  Macro scr_to_cpu() is to be used क्रम getting a DWORD 
 *  from the script.
 */

#घोषणा cpu_to_scr(dw)	cpu_to_le32(dw)
#घोषणा scr_to_cpu(dw)	le32_to_cpu(dw)

/*
 *  These ones are used as वापस code from 
 *  error recovery handlers under Linux.
 */
#घोषणा SCSI_SUCCESS	SUCCESS
#घोषणा SCSI_FAILED	FAILED

/*
 *  System specअगरic target data काष्ठाure.
 *  None क्रम now, under Linux.
 */
/* #घोषणा SYM_HAVE_STCB */

/*
 *  System specअगरic lun data काष्ठाure.
 */
#घोषणा SYM_HAVE_SLCB
काष्ठा sym_slcb अणु
	u_लघु	reqtags;	/* Number of tags requested by user */
	u_लघु scdev_depth;	/* Queue depth set in select_queue_depth() */
पूर्ण;

/*
 *  System specअगरic command data काष्ठाure.
 *  Not needed under Linux.
 */
/* काष्ठा sym_sccb */

/*
 *  System specअगरic host data काष्ठाure.
 */
काष्ठा sym_shcb अणु
	/*
	 *  Chip and controller identअगरication.
	 */
	पूर्णांक		unit;
	अक्षर		inst_name[16];
	अक्षर		chip_name[8];

	काष्ठा Scsi_Host *host;

	व्योम __iomem *	ioaddr;		/* MMIO kernel io address	*/
	व्योम __iomem *	ramaddr;	/* RAM  kernel io address	*/

	काष्ठा समयr_list समयr;	/* Timer handler link header	*/
	u_दीर्घ		lastसमय;
	u_दीर्घ		settle_समय;	/* Resetting the SCSI BUS	*/
	u_अक्षर		settle_समय_valid;
पूर्ण;

/*
 *  Return the name of the controller.
 */
#घोषणा sym_name(np) (np)->s.inst_name

काष्ठा sym_nvram;

/*
 * The IO macros require a काष्ठा called 's' and are abused in sym_nvram.c
 */
काष्ठा sym_device अणु
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ mmio_base;
	अचिन्हित दीर्घ ram_base;
	काष्ठा अणु
		व्योम __iomem *ioaddr;
		व्योम __iomem *ramaddr;
	पूर्ण s;
	काष्ठा sym_chip chip;
	काष्ठा sym_nvram *nvram;
	u_अक्षर host_id;
पूर्ण;

/*
 *  Driver host data काष्ठाure.
 */
काष्ठा sym_data अणु
	काष्ठा sym_hcb *ncb;
	काष्ठा completion *io_reset;		/* PCI error handling */
	काष्ठा pci_dev *pdev;
पूर्ण;

अटल अंतरभूत काष्ठा sym_hcb * sym_get_hcb(काष्ठा Scsi_Host *host)
अणु
	वापस ((काष्ठा sym_data *)host->hostdata)->ncb;
पूर्ण

#समावेश "sym_fw.h"
#समावेश "sym_hipd.h"

/*
 *  Set the status field of a CAM CCB.
 */
अटल अंतरभूत व्योम
sym_set_cam_status(काष्ठा scsi_cmnd *cmd, पूर्णांक status)
अणु
	cmd->result &= ~(0xff  << 16);
	cmd->result |= (status << 16);
पूर्ण

/*
 *  Get the status field of a CAM CCB.
 */
अटल अंतरभूत पूर्णांक
sym_get_cam_status(काष्ठा scsi_cmnd *cmd)
अणु
	वापस host_byte(cmd->result);
पूर्ण

/*
 *  Build CAM result क्रम a successful IO and क्रम a failed IO.
 */
अटल अंतरभूत व्योम sym_set_cam_result_ok(काष्ठा sym_ccb *cp, काष्ठा scsi_cmnd *cmd, पूर्णांक resid)
अणु
	scsi_set_resid(cmd, resid);
	cmd->result = (DID_OK << 16) | (cp->ssss_status & 0x7f);
पूर्ण
व्योम sym_set_cam_result_error(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp, पूर्णांक resid);

व्योम sym_xpt_करोne(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *ccb);
#घोषणा sym_prपूर्णांक_addr(cmd, arg...) dev_info(&cmd->device->sdev_gendev , ## arg)
व्योम sym_xpt_async_bus_reset(काष्ठा sym_hcb *np);
पूर्णांक  sym_setup_data_and_start (काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *csio, काष्ठा sym_ccb *cp);
व्योम sym_log_bus_error(काष्ठा Scsi_Host *);
व्योम sym_dump_रेजिस्टरs(काष्ठा Scsi_Host *);

#पूर्ण_अगर /* SYM_GLUE_H */
