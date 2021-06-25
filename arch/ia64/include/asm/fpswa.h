<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_FPSWA_H
#घोषणा _ASM_IA64_FPSWA_H

/*
 * Floating-poपूर्णांक Software Assist
 *
 * Copyright (C) 1999 Intel Corporation.
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 1999 Goutham Rao <goutham.rao@पूर्णांकel.com>
 */

प्रकार काष्ठा अणु
	/* 4 * 128 bits */
	अचिन्हित दीर्घ fp_lp[4*2];
पूर्ण fp_state_low_preserved_t;

प्रकार काष्ठा अणु
	/* 10 * 128 bits */
	अचिन्हित दीर्घ fp_lv[10 * 2];
पूर्ण fp_state_low_अस्थिर_t;

प्रकार	काष्ठा अणु
	/* 16 * 128 bits */
	अचिन्हित दीर्घ fp_hp[16 * 2];
पूर्ण fp_state_high_preserved_t;

प्रकार काष्ठा अणु
	/* 96 * 128 bits */
	अचिन्हित दीर्घ fp_hv[96 * 2];
पूर्ण fp_state_high_अस्थिर_t;

/**
 * भग्नing poपूर्णांक state to be passed to the FP emulation library by
 * the trap/fault handler
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ			biपंचांगask_low64;
	अचिन्हित दीर्घ			biपंचांगask_high64;
	fp_state_low_preserved_t	*fp_state_low_preserved;
	fp_state_low_अस्थिर_t		*fp_state_low_अस्थिर;
	fp_state_high_preserved_t	*fp_state_high_preserved;
	fp_state_high_अस्थिर_t	*fp_state_high_अस्थिर;
पूर्ण fp_state_t;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ err0;
	अचिन्हित दीर्घ err1;
	अचिन्हित दीर्घ err2;
पूर्ण fpswa_ret_t;

/**
 * function header क्रम the Floating Poपूर्णांक software assist
 * library. This function is invoked by the Floating poपूर्णांक software
 * assist trap/fault handler.
 */
प्रकार fpswa_ret_t (*efi_fpswa_t) (अचिन्हित दीर्घ trap_type, व्योम *bundle, अचिन्हित दीर्घ *ipsr,
				    अचिन्हित दीर्घ *fsr, अचिन्हित दीर्घ *isr, अचिन्हित दीर्घ *preds,
				    अचिन्हित दीर्घ *अगरs, fp_state_t *fp_state);

/**
 * This is the FPSWA library पूर्णांकerface as defined by EFI.  We need to pass a 
 * poपूर्णांकer to the पूर्णांकerface itself on a call to the assist library
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक	 revision;
	अचिन्हित पूर्णांक	 reserved;
	efi_fpswa_t	 fpswa;
पूर्ण fpswa_पूर्णांकerface_t;

बाह्य fpswa_पूर्णांकerface_t *fpswa_पूर्णांकerface;

#पूर्ण_अगर /* _ASM_IA64_FPSWA_H */
