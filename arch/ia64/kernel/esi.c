<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Extensible SAL Interface (ESI) support routines.
 *
 * Copyright (C) 2006 Hewlett-Packard Co
 * 	Alex Williamson <alex.williamson@hp.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/esi.h>
#समावेश <यंत्र/sal.h>

MODULE_AUTHOR("Alex Williamson <alex.williamson@hp.com>");
MODULE_DESCRIPTION("Extensible SAL Interface (ESI) support");
MODULE_LICENSE("GPL");

#घोषणा MODULE_NAME	"esi"

क्रमागत esi_systab_entry_type अणु
	ESI_DESC_ENTRY_POINT = 0
पूर्ण;

/*
 * Entry type:	Size:
 *	0	48
 */
#घोषणा ESI_DESC_SIZE(type)	"\060"[(अचिन्हित) (type)]

प्रकार काष्ठा ia64_esi_desc_entry_poपूर्णांक अणु
	u8 type;
	u8 reserved1[15];
	u64 esi_proc;
	u64 gp;
	efi_guid_t guid;
पूर्ण ia64_esi_desc_entry_poपूर्णांक_t;

काष्ठा pdesc अणु
	व्योम *addr;
	व्योम *gp;
पूर्ण;

अटल काष्ठा ia64_sal_systab *esi_systab;

बाह्य अचिन्हित दीर्घ esi_phys;

अटल पूर्णांक __init esi_init (व्योम)
अणु
	काष्ठा ia64_sal_systab *systab;
	अक्षर *p;
	पूर्णांक i;

	अगर (esi_phys == EFI_INVALID_TABLE_ADDR)
		वापस -ENODEV;

	systab = __va(esi_phys);

	अगर (म_भेदन(systab->signature, "ESIT", 4) != 0) अणु
		prपूर्णांकk(KERN_ERR "bad signature in ESI system table!");
		वापस -ENODEV;
	पूर्ण

	p = (अक्षर *) (systab + 1);
	क्रम (i = 0; i < systab->entry_count; i++) अणु
		/*
		 * The first byte of each entry type contains the type
		 * descriptor.
		 */
		चयन (*p) अणु
		      हाल ESI_DESC_ENTRY_POINT:
			अवरोध;
		      शेष:
			prपूर्णांकk(KERN_WARNING "Unknown table type %d found in "
			       "ESI table, ignoring rest of table\n", *p);
			वापस -ENODEV;
		पूर्ण

		p += ESI_DESC_SIZE(*p);
	पूर्ण

	esi_systab = systab;
	वापस 0;
पूर्ण


पूर्णांक ia64_esi_call (efi_guid_t guid, काष्ठा ia64_sal_retval *isrvp,
		   क्रमागत esi_proc_type proc_type, u64 func,
		   u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6,
		   u64 arg7)
अणु
	काष्ठा ia64_fpreg fr[6];
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक i;
	अक्षर *p;

	अगर (!esi_systab)
		वापस -1;

	p = (अक्षर *) (esi_systab + 1);
	क्रम (i = 0; i < esi_systab->entry_count; i++) अणु
		अगर (*p == ESI_DESC_ENTRY_POINT) अणु
			ia64_esi_desc_entry_poपूर्णांक_t *esi = (व्योम *)p;
			अगर (!efi_guidcmp(guid, esi->guid)) अणु
				ia64_sal_handler esi_proc;
				काष्ठा pdesc pdesc;

				pdesc.addr = __va(esi->esi_proc);
				pdesc.gp = __va(esi->gp);

				esi_proc = (ia64_sal_handler) &pdesc;

				ia64_save_scratch_fpregs(fr);
				अगर (proc_type == ESI_PROC_SERIALIZED)
					spin_lock_irqsave(&sal_lock, flags);
				अन्यथा अगर (proc_type == ESI_PROC_MP_SAFE)
					local_irq_save(flags);
				अन्यथा
					preempt_disable();
				*isrvp = (*esi_proc)(func, arg1, arg2, arg3,
						     arg4, arg5, arg6, arg7);
				अगर (proc_type == ESI_PROC_SERIALIZED)
					spin_unlock_irqrestore(&sal_lock,
							       flags);
				अन्यथा अगर (proc_type == ESI_PROC_MP_SAFE)
					local_irq_restore(flags);
				अन्यथा
					preempt_enable();
				ia64_load_scratch_fpregs(fr);
				वापस 0;
			पूर्ण
		पूर्ण
		p += ESI_DESC_SIZE(*p);
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(ia64_esi_call);

पूर्णांक ia64_esi_call_phys (efi_guid_t guid, काष्ठा ia64_sal_retval *isrvp,
			u64 func, u64 arg1, u64 arg2, u64 arg3, u64 arg4,
			u64 arg5, u64 arg6, u64 arg7)
अणु
	काष्ठा ia64_fpreg fr[6];
	अचिन्हित दीर्घ flags;
	u64 esi_params[8];
	अक्षर *p;
	पूर्णांक i;

	अगर (!esi_systab)
		वापस -1;

	p = (अक्षर *) (esi_systab + 1);
	क्रम (i = 0; i < esi_systab->entry_count; i++) अणु
		अगर (*p == ESI_DESC_ENTRY_POINT) अणु
			ia64_esi_desc_entry_poपूर्णांक_t *esi = (व्योम *)p;
			अगर (!efi_guidcmp(guid, esi->guid)) अणु
				ia64_sal_handler esi_proc;
				काष्ठा pdesc pdesc;

				pdesc.addr = (व्योम *)esi->esi_proc;
				pdesc.gp = (व्योम *)esi->gp;

				esi_proc = (ia64_sal_handler) &pdesc;

				esi_params[0] = func;
				esi_params[1] = arg1;
				esi_params[2] = arg2;
				esi_params[3] = arg3;
				esi_params[4] = arg4;
				esi_params[5] = arg5;
				esi_params[6] = arg6;
				esi_params[7] = arg7;
				ia64_save_scratch_fpregs(fr);
				spin_lock_irqsave(&sal_lock, flags);
				*isrvp = esi_call_phys(esi_proc, esi_params);
				spin_unlock_irqrestore(&sal_lock, flags);
				ia64_load_scratch_fpregs(fr);
				वापस 0;
			पूर्ण
		पूर्ण
		p += ESI_DESC_SIZE(*p);
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(ia64_esi_call_phys);

अटल व्योम __निकास esi_निकास (व्योम)
अणु
पूर्ण

module_init(esi_init);
module_निकास(esi_निकास);	/* makes module removable... */
