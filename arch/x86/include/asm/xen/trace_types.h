<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_XEN_TRACE_TYPES_H
#घोषणा _ASM_XEN_TRACE_TYPES_H

क्रमागत xen_mc_flush_reason अणु
	XEN_MC_FL_NONE,		/* explicit flush */
	XEN_MC_FL_BATCH,	/* out of hypercall space */
	XEN_MC_FL_ARGS,		/* out of argument space */
	XEN_MC_FL_CALLBACK,	/* out of callback space */
पूर्ण;

क्रमागत xen_mc_extend_args अणु
	XEN_MC_XE_OK,
	XEN_MC_XE_BAD_OP,
	XEN_MC_XE_NO_SPACE
पूर्ण;
प्रकार व्योम (*xen_mc_callback_fn_t)(व्योम *);

#पूर्ण_अगर	/* _ASM_XEN_TRACE_TYPES_H */
