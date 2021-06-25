<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux Guest Relocation (LGR) detection
 *
 * Copyright IBM Corp. 2012
 * Author(s): Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/ipl.h>

#घोषणा LGR_TIMER_INTERVAL_SECS (30 * 60)
#घोषणा VM_LEVEL_MAX 2 /* Maximum is 8, but we only record two levels */

/*
 * LGR info: Contains stfle and stsi data
 */
काष्ठा lgr_info अणु
	/* Bit field with facility inक्रमmation: 4 DWORDs are stored */
	u64 stfle_fac_list[4];
	/* Level of प्रणाली (1 = CEC, 2 = LPAR, 3 = z/VM */
	u32 level;
	/* Level 1: CEC info (stsi 1.1.1) */
	अक्षर manufacturer[16];
	अक्षर type[4];
	अक्षर sequence[16];
	अक्षर plant[4];
	अक्षर model[16];
	/* Level 2: LPAR info (stsi 2.2.2) */
	u16 lpar_number;
	अक्षर name[8];
	/* Level 3: VM info (stsi 3.2.2) */
	u8 vm_count;
	काष्ठा अणु
		अक्षर name[8];
		अक्षर cpi[16];
	पूर्ण vm[VM_LEVEL_MAX];
पूर्ण __packed __aligned(8);

/*
 * LGR globals
 */
अटल अक्षर lgr_page[PAGE_SIZE] __aligned(PAGE_SIZE);
अटल काष्ठा lgr_info lgr_info_last;
अटल काष्ठा lgr_info lgr_info_cur;
अटल काष्ठा debug_info *lgr_dbf;

/*
 * Copy buffer and then convert it to ASCII
 */
अटल व्योम cpascii(अक्षर *dst, अक्षर *src, पूर्णांक size)
अणु
	स_नकल(dst, src, size);
	EBCASC(dst, size);
पूर्ण

/*
 * Fill LGR info with 1.1.1 stsi data
 */
अटल व्योम lgr_stsi_1_1_1(काष्ठा lgr_info *lgr_info)
अणु
	काष्ठा sysinfo_1_1_1 *si = (व्योम *) lgr_page;

	अगर (stsi(si, 1, 1, 1))
		वापस;
	cpascii(lgr_info->manufacturer, si->manufacturer,
		माप(si->manufacturer));
	cpascii(lgr_info->type, si->type, माप(si->type));
	cpascii(lgr_info->model, si->model, माप(si->model));
	cpascii(lgr_info->sequence, si->sequence, माप(si->sequence));
	cpascii(lgr_info->plant, si->plant, माप(si->plant));
पूर्ण

/*
 * Fill LGR info with 2.2.2 stsi data
 */
अटल व्योम lgr_stsi_2_2_2(काष्ठा lgr_info *lgr_info)
अणु
	काष्ठा sysinfo_2_2_2 *si = (व्योम *) lgr_page;

	अगर (stsi(si, 2, 2, 2))
		वापस;
	cpascii(lgr_info->name, si->name, माप(si->name));
	स_नकल(&lgr_info->lpar_number, &si->lpar_number,
	       माप(lgr_info->lpar_number));
पूर्ण

/*
 * Fill LGR info with 3.2.2 stsi data
 */
अटल व्योम lgr_stsi_3_2_2(काष्ठा lgr_info *lgr_info)
अणु
	काष्ठा sysinfo_3_2_2 *si = (व्योम *) lgr_page;
	पूर्णांक i;

	अगर (stsi(si, 3, 2, 2))
		वापस;
	क्रम (i = 0; i < min_t(u8, si->count, VM_LEVEL_MAX); i++) अणु
		cpascii(lgr_info->vm[i].name, si->vm[i].name,
			माप(si->vm[i].name));
		cpascii(lgr_info->vm[i].cpi, si->vm[i].cpi,
			माप(si->vm[i].cpi));
	पूर्ण
	lgr_info->vm_count = si->count;
पूर्ण

/*
 * Fill LGR info with current data
 */
अटल व्योम lgr_info_get(काष्ठा lgr_info *lgr_info)
अणु
	पूर्णांक level;

	स_रखो(lgr_info, 0, माप(*lgr_info));
	stfle(lgr_info->stfle_fac_list, ARRAY_SIZE(lgr_info->stfle_fac_list));
	level = stsi(शून्य, 0, 0, 0);
	lgr_info->level = level;
	अगर (level >= 1)
		lgr_stsi_1_1_1(lgr_info);
	अगर (level >= 2)
		lgr_stsi_2_2_2(lgr_info);
	अगर (level >= 3)
		lgr_stsi_3_2_2(lgr_info);
पूर्ण

/*
 * Check अगर LGR info has changed and अगर yes log new LGR info to s390dbf
 */
व्योम lgr_info_log(व्योम)
अणु
	अटल DEFINE_SPINLOCK(lgr_info_lock);
	अचिन्हित दीर्घ flags;

	अगर (!spin_trylock_irqsave(&lgr_info_lock, flags))
		वापस;
	lgr_info_get(&lgr_info_cur);
	अगर (स_भेद(&lgr_info_last, &lgr_info_cur, माप(lgr_info_cur)) != 0) अणु
		debug_event(lgr_dbf, 1, &lgr_info_cur, माप(lgr_info_cur));
		lgr_info_last = lgr_info_cur;
	पूर्ण
	spin_unlock_irqrestore(&lgr_info_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(lgr_info_log);

अटल व्योम lgr_समयr_set(व्योम);

/*
 * LGR समयr callback
 */
अटल व्योम lgr_समयr_fn(काष्ठा समयr_list *unused)
अणु
	lgr_info_log();
	lgr_समयr_set();
पूर्ण

अटल काष्ठा समयr_list lgr_समयr;

/*
 * Setup next LGR समयr
 */
अटल व्योम lgr_समयr_set(व्योम)
अणु
	mod_समयr(&lgr_समयr, jअगरfies + msecs_to_jअगरfies(LGR_TIMER_INTERVAL_SECS * MSEC_PER_SEC));
पूर्ण

/*
 * Initialize LGR: Add s390dbf, ग_लिखो initial lgr_info and setup समयr
 */
अटल पूर्णांक __init lgr_init(व्योम)
अणु
	lgr_dbf = debug_रेजिस्टर("lgr", 1, 1, माप(काष्ठा lgr_info));
	अगर (!lgr_dbf)
		वापस -ENOMEM;
	debug_रेजिस्टर_view(lgr_dbf, &debug_hex_ascii_view);
	lgr_info_get(&lgr_info_last);
	debug_event(lgr_dbf, 1, &lgr_info_last, माप(lgr_info_last));
	समयr_setup(&lgr_समयr, lgr_समयr_fn, TIMER_DEFERRABLE);
	lgr_समयr_set();
	वापस 0;
पूर्ण
device_initcall(lgr_init);
