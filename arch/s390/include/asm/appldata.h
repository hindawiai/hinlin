<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2006
 *
 * Author(s): Melissa Howland <melissah@us.ibm.com>
 */

#अगर_अघोषित _ASM_S390_APPLDATA_H
#घोषणा _ASM_S390_APPLDATA_H

#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/पन.स>

#घोषणा APPLDATA_START_INTERVAL_REC	0x80
#घोषणा APPLDATA_STOP_REC		0x81
#घोषणा APPLDATA_GEN_EVENT_REC		0x82
#घोषणा APPLDATA_START_CONFIG_REC	0x83

/*
 * Parameter list क्रम DIAGNOSE X'DC'
 */
काष्ठा appldata_parameter_list अणु
	u16 diag;
	u8  function;
	u8  parlist_length;
	u32 unused01;
	u16 reserved;
	u16 buffer_length;
	u32 unused02;
	u64 product_id_addr;
	u64 buffer_addr;
पूर्ण __attribute__ ((packed));

काष्ठा appldata_product_id अणु
	अक्षर prod_nr[7];	/* product number */
	u16  prod_fn;		/* product function */
	u8   record_nr; 	/* record number */
	u16  version_nr;	/* version */
	u16  release_nr;	/* release */
	u16  mod_lvl;		/* modअगरication level */
पूर्ण __attribute__ ((packed));


अटल अंतरभूत पूर्णांक appldata_यंत्र(काष्ठा appldata_parameter_list *parm_list,
			       काष्ठा appldata_product_id *id,
			       अचिन्हित लघु fn, व्योम *buffer,
			       अचिन्हित लघु length)
अणु
	पूर्णांक ry;

	अगर (!MACHINE_IS_VM)
		वापस -EOPNOTSUPP;
	parm_list->diag = 0xdc;
	parm_list->function = fn;
	parm_list->parlist_length = माप(*parm_list);
	parm_list->buffer_length = length;
	parm_list->product_id_addr = (अचिन्हित दीर्घ) id;
	parm_list->buffer_addr = virt_to_phys(buffer);
	diag_stat_inc(DIAG_STAT_X0DC);
	यंत्र अस्थिर(
		"	diag	%1,%0,0xdc"
		: "=d" (ry)
		: "d" (parm_list), "m" (*parm_list), "m" (*id)
		: "cc");
	वापस ry;
पूर्ण

#पूर्ण_अगर /* _ASM_S390_APPLDATA_H */
