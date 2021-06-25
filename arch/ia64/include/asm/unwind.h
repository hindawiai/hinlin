<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_UNWIND_H
#घोषणा _ASM_IA64_UNWIND_H

/*
 * Copyright (C) 1999-2000, 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * A simple API क्रम unwinding kernel stacks.  This is used क्रम
 * debugging and error reporting purposes.  The kernel करोesn't need
 * full-blown stack unwinding with all the bells and whitles, so there
 * is not much poपूर्णांक in implementing the full IA-64 unwind API (though
 * it would of course be possible to implement the kernel API on top
 * of it).
 */

काष्ठा task_काष्ठा;	/* क्रमward declaration */
काष्ठा चयन_stack;	/* क्रमward declaration */

क्रमागत unw_application_रेजिस्टर अणु
	UNW_AR_BSP,
	UNW_AR_BSPSTORE,
	UNW_AR_PFS,
	UNW_AR_RNAT,
	UNW_AR_UNAT,
	UNW_AR_LC,
	UNW_AR_EC,
	UNW_AR_FPSR,
	UNW_AR_RSC,
	UNW_AR_CCV,
	UNW_AR_CSD,
	UNW_AR_SSD
पूर्ण;

/*
 * The following declarations are निजी to the unwind
 * implementation:
 */

काष्ठा unw_stack अणु
	अचिन्हित दीर्घ limit;
	अचिन्हित दीर्घ top;
पूर्ण;

#घोषणा UNW_FLAG_INTERRUPT_FRAME	(1UL << 0)

/*
 * No user of this module should every access this काष्ठाure directly
 * as it is subject to change.  It is declared here solely so we can
 * use स्वतःmatic variables.
 */
काष्ठा unw_frame_info अणु
	काष्ठा unw_stack regstk;
	काष्ठा unw_stack memstk;
	अचिन्हित पूर्णांक flags;
	लघु hपूर्णांक;
	लघु prev_script;

	/* current frame info: */
	अचिन्हित दीर्घ bsp;		/* backing store poपूर्णांकer value */
	अचिन्हित दीर्घ sp;		/* stack poपूर्णांकer value */
	अचिन्हित दीर्घ psp;		/* previous sp value */
	अचिन्हित दीर्घ ip;		/* inकाष्ठाion poपूर्णांकer value */
	अचिन्हित दीर्घ pr;		/* current predicate values */
	अचिन्हित दीर्घ *cfm_loc;		/* cfm save location (or शून्य) */
	अचिन्हित दीर्घ pt;		/* काष्ठा pt_regs location */

	काष्ठा task_काष्ठा *task;
	काष्ठा चयन_stack *sw;

	/* preserved state: */
	अचिन्हित दीर्घ *bsp_loc;		/* previous bsp save location */
	अचिन्हित दीर्घ *bspstore_loc;
	अचिन्हित दीर्घ *pfs_loc;
	अचिन्हित दीर्घ *rnat_loc;
	अचिन्हित दीर्घ *rp_loc;
	अचिन्हित दीर्घ *pri_unat_loc;
	अचिन्हित दीर्घ *unat_loc;
	अचिन्हित दीर्घ *pr_loc;
	अचिन्हित दीर्घ *lc_loc;
	अचिन्हित दीर्घ *fpsr_loc;
	काष्ठा unw_ireg अणु
		अचिन्हित दीर्घ *loc;
		काष्ठा unw_ireg_nat अणु
			अचिन्हित दीर्घ type : 3;		/* क्रमागत unw_nat_type */
			चिन्हित दीर्घ off : 61;		/* NaT word is at loc+nat.off */
		पूर्ण nat;
	पूर्ण r4, r5, r6, r7;
	अचिन्हित दीर्घ *b1_loc, *b2_loc, *b3_loc, *b4_loc, *b5_loc;
	काष्ठा ia64_fpreg *f2_loc, *f3_loc, *f4_loc, *f5_loc, *fr_loc[16];
पूर्ण;

/*
 * The official API follows below:
 */

काष्ठा unw_table_entry अणु
	u64 start_offset;
	u64 end_offset;
	u64 info_offset;
पूर्ण;

/*
 * Initialize unwind support.
 */
बाह्य व्योम unw_init (व्योम);

बाह्य व्योम *unw_add_unwind_table (स्थिर अक्षर *name, अचिन्हित दीर्घ segment_base, अचिन्हित दीर्घ gp,
				   स्थिर व्योम *table_start, स्थिर व्योम *table_end);

बाह्य व्योम unw_हटाओ_unwind_table (व्योम *handle);

/*
 * Prepare to unwind blocked task t.
 */
बाह्य व्योम unw_init_from_blocked_task (काष्ठा unw_frame_info *info, काष्ठा task_काष्ठा *t);

बाह्य व्योम unw_init_frame_info (काष्ठा unw_frame_info *info, काष्ठा task_काष्ठा *t,
				 काष्ठा चयन_stack *sw);

/*
 * Prepare to unwind the currently running thपढ़ो.
 */
बाह्य व्योम unw_init_running (व्योम (*callback)(काष्ठा unw_frame_info *info, व्योम *arg), व्योम *arg);

/*
 * Unwind to previous to frame.  Returns 0 अगर successful, negative
 * number in हाल of an error.
 */
बाह्य पूर्णांक unw_unwind (काष्ठा unw_frame_info *info);

/*
 * Unwind until the वापस poपूर्णांकer is in user-land (or until an error
 * occurs).  Returns 0 अगर successful, negative number in हाल of
 * error.
 */
बाह्य पूर्णांक unw_unwind_to_user (काष्ठा unw_frame_info *info);

#घोषणा unw_is_पूर्णांकr_frame(info)	(((info)->flags & UNW_FLAG_INTERRUPT_FRAME) != 0)

अटल अंतरभूत पूर्णांक
unw_get_ip (काष्ठा unw_frame_info *info, अचिन्हित दीर्घ *valp)
अणु
	*valp = (info)->ip;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
unw_get_sp (काष्ठा unw_frame_info *info, अचिन्हित दीर्घ *valp)
अणु
	*valp = (info)->sp;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
unw_get_psp (काष्ठा unw_frame_info *info, अचिन्हित दीर्घ *valp)
अणु
	*valp = (info)->psp;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
unw_get_bsp (काष्ठा unw_frame_info *info, अचिन्हित दीर्घ *valp)
अणु
	*valp = (info)->bsp;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
unw_get_cfm (काष्ठा unw_frame_info *info, अचिन्हित दीर्घ *valp)
अणु
	*valp = *(info)->cfm_loc;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
unw_set_cfm (काष्ठा unw_frame_info *info, अचिन्हित दीर्घ val)
अणु
	*(info)->cfm_loc = val;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
unw_get_rp (काष्ठा unw_frame_info *info, अचिन्हित दीर्घ *val)
अणु
	अगर (!info->rp_loc)
		वापस -1;
	*val = *info->rp_loc;
	वापस 0;
पूर्ण

बाह्य पूर्णांक unw_access_gr (काष्ठा unw_frame_info *, पूर्णांक, अचिन्हित दीर्घ *, अक्षर *, पूर्णांक);
बाह्य पूर्णांक unw_access_br (काष्ठा unw_frame_info *, पूर्णांक, अचिन्हित दीर्घ *, पूर्णांक);
बाह्य पूर्णांक unw_access_fr (काष्ठा unw_frame_info *, पूर्णांक, काष्ठा ia64_fpreg *, पूर्णांक);
बाह्य पूर्णांक unw_access_ar (काष्ठा unw_frame_info *, पूर्णांक, अचिन्हित दीर्घ *, पूर्णांक);
बाह्य पूर्णांक unw_access_pr (काष्ठा unw_frame_info *, अचिन्हित दीर्घ *, पूर्णांक);

अटल अंतरभूत पूर्णांक
unw_set_gr (काष्ठा unw_frame_info *i, पूर्णांक n, अचिन्हित दीर्घ v, अक्षर nat)
अणु
	वापस unw_access_gr(i, n, &v, &nat, 1);
पूर्ण

अटल अंतरभूत पूर्णांक
unw_set_br (काष्ठा unw_frame_info *i, पूर्णांक n, अचिन्हित दीर्घ v)
अणु
	वापस unw_access_br(i, n, &v, 1);
पूर्ण

अटल अंतरभूत पूर्णांक
unw_set_fr (काष्ठा unw_frame_info *i, पूर्णांक n, काष्ठा ia64_fpreg v)
अणु
	वापस unw_access_fr(i, n, &v, 1);
पूर्ण

अटल अंतरभूत पूर्णांक
unw_set_ar (काष्ठा unw_frame_info *i, पूर्णांक n, अचिन्हित दीर्घ v)
अणु
	वापस unw_access_ar(i, n, &v, 1);
पूर्ण

अटल अंतरभूत पूर्णांक
unw_set_pr (काष्ठा unw_frame_info *i, अचिन्हित दीर्घ v)
अणु
	वापस unw_access_pr(i, &v, 1);
पूर्ण

#घोषणा unw_get_gr(i,n,v,nat)	unw_access_gr(i,n,v,nat,0)
#घोषणा unw_get_br(i,n,v)	unw_access_br(i,n,v,0)
#घोषणा unw_get_fr(i,n,v)	unw_access_fr(i,n,v,0)
#घोषणा unw_get_ar(i,n,v)	unw_access_ar(i,n,v,0)
#घोषणा unw_get_pr(i,v)		unw_access_pr(i,v,0)

#पूर्ण_अगर /* _ASM_UNWIND_H */
