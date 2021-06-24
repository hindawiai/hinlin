<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ATP870U_H
#घोषणा _ATP870U_H

#समावेश <linux/types.h>
#समावेश <linux/kdev_t.h>

/* I/O Port */

#घोषणा MAX_CDB		12
#घोषणा MAX_SENSE	14
#घोषणा qcnt		32
#घोषणा ATP870U_SCATTER	128

#घोषणा MAX_ADAPTER	8
#घोषणा MAX_SCSI_ID	16
#घोषणा ATP870U_MAX_SECTORS 128

#घोषणा ATP885_DEVID 0x808A
#घोषणा ATP880_DEVID1 0x8080
#घोषणा ATP880_DEVID2 0x8081

//#घोषणा ED_DBGP

काष्ठा atp_unit
अणु
	अचिन्हित दीर्घ baseport;
	अचिन्हित दीर्घ ioport[2];
	अचिन्हित दीर्घ pciport[2];
	अचिन्हित अक्षर last_cmd[2];
	अचिन्हित अक्षर in_snd[2];
	अचिन्हित अक्षर in_पूर्णांक[2];
	अचिन्हित अक्षर quhd[2];
	अचिन्हित अक्षर quend[2];
	अचिन्हित अक्षर global_map[2];
	अचिन्हित अक्षर host_id[2];
	अचिन्हित पूर्णांक working[2];
	अचिन्हित लघु wide_id[2];
	अचिन्हित लघु active_id[2];
	अचिन्हित लघु ultra_map[2];
	अचिन्हित लघु async[2];
	अचिन्हित अक्षर sp[2][16];
	अचिन्हित अक्षर r1f[2][16];
	काष्ठा scsi_cmnd *quereq[2][qcnt];
	काष्ठा atp_id
	अणु
		अचिन्हित अक्षर dirct;
		अचिन्हित अक्षर devsp;
		अचिन्हित अक्षर devtype;
		अचिन्हित दीर्घ tran_len;
		अचिन्हित दीर्घ last_len;
		अचिन्हित अक्षर *prd_pos;
		अचिन्हित अक्षर *prd_table;	/* Kernel address of PRD table */
		dma_addr_t prd_bus;		/* Bus address of PRD */
		dma_addr_t prdaddr;		/* Dynamically updated in driver */
		काष्ठा scsi_cmnd *curr_req;
	पूर्ण id[2][16];
	काष्ठा Scsi_Host *host;
	काष्ठा pci_dev *pdev;
	अचिन्हित पूर्णांक unit;
पूर्ण;

#पूर्ण_अगर
