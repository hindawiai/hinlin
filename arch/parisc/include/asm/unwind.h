<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _UNWIND_H_
#घोषणा _UNWIND_H_

#समावेश <linux/list.h>

/* Max number of levels to backtrace */
#घोषणा MAX_UNWIND_ENTRIES	30

/* From ABI specअगरications */
काष्ठा unwind_table_entry अणु
	अचिन्हित पूर्णांक region_start;
	अचिन्हित पूर्णांक region_end;
	अचिन्हित पूर्णांक Cannot_unwind:1; /* 0 */
	अचिन्हित पूर्णांक Millicode:1;	/* 1 */
	अचिन्हित पूर्णांक Millicode_save_sr0:1;	/* 2 */
	अचिन्हित पूर्णांक Region_description:2;	/* 3..4 */
	अचिन्हित पूर्णांक reserved1:1;	/* 5 */
	अचिन्हित पूर्णांक Entry_SR:1;	/* 6 */
	अचिन्हित पूर्णांक Entry_FR:4;	/* number saved *//* 7..10 */
	अचिन्हित पूर्णांक Entry_GR:5;	/* number saved *//* 11..15 */
	अचिन्हित पूर्णांक Args_stored:1;	/* 16 */
	अचिन्हित पूर्णांक Variable_Frame:1;	/* 17 */
	अचिन्हित पूर्णांक Separate_Package_Body:1;	/* 18 */
	अचिन्हित पूर्णांक Frame_Extension_Millicode:1;	/* 19 */
	अचिन्हित पूर्णांक Stack_Overflow_Check:1;	/* 20 */
	अचिन्हित पूर्णांक Two_Inकाष्ठाion_SP_Increment:1;	/* 21 */
	अचिन्हित पूर्णांक Ada_Region:1;	/* 22 */
	अचिन्हित पूर्णांक cxx_info:1;	/* 23 */
	अचिन्हित पूर्णांक cxx_try_catch:1;	/* 24 */
	अचिन्हित पूर्णांक sched_entry_seq:1;	/* 25 */
	अचिन्हित पूर्णांक reserved2:1;	/* 26 */
	अचिन्हित पूर्णांक Save_SP:1;	/* 27 */
	अचिन्हित पूर्णांक Save_RP:1;	/* 28 */
	अचिन्हित पूर्णांक Save_MRP_in_frame:1;	/* 29 */
	अचिन्हित पूर्णांक extn_ptr_defined:1;	/* 30 */
	अचिन्हित पूर्णांक Cleanup_defined:1;	/* 31 */
	
	अचिन्हित पूर्णांक MPE_XL_पूर्णांकerrupt_marker:1;	/* 0 */
	अचिन्हित पूर्णांक HP_UX_पूर्णांकerrupt_marker:1;	/* 1 */
	अचिन्हित पूर्णांक Large_frame:1;	/* 2 */
	अचिन्हित पूर्णांक Pseuकरो_SP_Set:1;	/* 3 */
	अचिन्हित पूर्णांक reserved4:1;	/* 4 */
	अचिन्हित पूर्णांक Total_frame_size:27;	/* 5..31 */
पूर्ण;

काष्ठा unwind_table अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ gp;
	अचिन्हित दीर्घ base_addr;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	स्थिर काष्ठा unwind_table_entry *table;
	अचिन्हित दीर्घ length;
पूर्ण;

काष्ठा unwind_frame_info अणु
	काष्ठा task_काष्ठा *t;
	/* Eventually we would like to be able to get at any of the रेजिस्टरs
	   available; but क्रम now we only try to get the sp and ip क्रम each
	   frame */
	/* काष्ठा pt_regs regs; */
	अचिन्हित दीर्घ sp, ip, rp, r31;
	अचिन्हित दीर्घ prev_sp, prev_ip;
पूर्ण;

काष्ठा unwind_table *
unwind_table_add(स्थिर अक्षर *name, अचिन्हित दीर्घ base_addr, 
		 अचिन्हित दीर्घ gp, व्योम *start, व्योम *end);
व्योम
unwind_table_हटाओ(काष्ठा unwind_table *table);

व्योम unwind_frame_init(काष्ठा unwind_frame_info *info, काष्ठा task_काष्ठा *t, 
		       काष्ठा pt_regs *regs);
व्योम unwind_frame_init_from_blocked_task(काष्ठा unwind_frame_info *info,
			काष्ठा task_काष्ठा *t);
व्योम unwind_frame_init_task(काष्ठा unwind_frame_info *info,
			काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs);
पूर्णांक unwind_once(काष्ठा unwind_frame_info *info);
पूर्णांक unwind_to_user(काष्ठा unwind_frame_info *info);

पूर्णांक unwind_init(व्योम);

#पूर्ण_अगर
