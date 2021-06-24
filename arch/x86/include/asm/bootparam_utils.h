<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_BOOTPARAM_UTILS_H
#घोषणा _ASM_X86_BOOTPARAM_UTILS_H

#समावेश <यंत्र/bootparam.h>

/*
 * This file is included from multiple environments.  Do not
 * add completing #समावेशs to make it standalone.
 */

/*
 * Deal with bootloaders which fail to initialize unknown fields in
 * boot_params to zero.  The list fields in this list are taken from
 * analysis of kexec-tools; अगर other broken bootloaders initialize a
 * dअगरferent set of fields we will need to figure out how to disambiguate.
 *
 * Note: efi_info is commonly left uninitialized, but that field has a
 * निजी magic, so it is better to leave it unchanged.
 */

#घोषणा माप_mbr(type, member) (अणु माप(((type *)0)->member); पूर्ण)

#घोषणा BOOT_PARAM_PRESERVE(काष्ठा_member)				\
	अणु								\
		.start = दुरत्व(काष्ठा boot_params, काष्ठा_member),	\
		.len   = माप_mbr(काष्ठा boot_params, काष्ठा_member),	\
	पूर्ण

काष्ठा boot_params_to_save अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक len;
पूर्ण;

अटल व्योम sanitize_boot_params(काष्ठा boot_params *boot_params)
अणु
	/* 
	 * IMPORTANT NOTE TO BOOTLOADER AUTHORS: करो not simply clear
	 * this field.  The purpose of this field is to guarantee
	 * compliance with the x86 boot spec located in
	 * Documentation/x86/boot.rst .  That spec says that the
	 * *whole* काष्ठाure should be cleared, after which only the
	 * portion defined by काष्ठा setup_header (boot_params->hdr)
	 * should be copied in.
	 *
	 * If you're having an issue because the sentinel is set, you
	 * need to change the whole काष्ठाure to be cleared, not this
	 * (or any other) inभागidual field, or you will soon have
	 * problems again.
	 */
	अगर (boot_params->sentinel) अणु
		अटल काष्ठा boot_params scratch;
		अक्षर *bp_base = (अक्षर *)boot_params;
		अक्षर *save_base = (अक्षर *)&scratch;
		पूर्णांक i;

		स्थिर काष्ठा boot_params_to_save to_save[] = अणु
			BOOT_PARAM_PRESERVE(screen_info),
			BOOT_PARAM_PRESERVE(apm_bios_info),
			BOOT_PARAM_PRESERVE(tboot_addr),
			BOOT_PARAM_PRESERVE(ist_info),
			BOOT_PARAM_PRESERVE(hd0_info),
			BOOT_PARAM_PRESERVE(hd1_info),
			BOOT_PARAM_PRESERVE(sys_desc_table),
			BOOT_PARAM_PRESERVE(olpc_ofw_header),
			BOOT_PARAM_PRESERVE(efi_info),
			BOOT_PARAM_PRESERVE(alt_mem_k),
			BOOT_PARAM_PRESERVE(scratch),
			BOOT_PARAM_PRESERVE(e820_entries),
			BOOT_PARAM_PRESERVE(eddbuf_entries),
			BOOT_PARAM_PRESERVE(edd_mbr_sig_buf_entries),
			BOOT_PARAM_PRESERVE(edd_mbr_sig_buffer),
			BOOT_PARAM_PRESERVE(secure_boot),
			BOOT_PARAM_PRESERVE(hdr),
			BOOT_PARAM_PRESERVE(e820_table),
			BOOT_PARAM_PRESERVE(eddbuf),
		पूर्ण;

		स_रखो(&scratch, 0, माप(scratch));

		क्रम (i = 0; i < ARRAY_SIZE(to_save); i++) अणु
			स_नकल(save_base + to_save[i].start,
			       bp_base + to_save[i].start, to_save[i].len);
		पूर्ण

		स_नकल(boot_params, save_base, माप(*boot_params));
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _ASM_X86_BOOTPARAM_UTILS_H */
