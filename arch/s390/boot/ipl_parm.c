<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/boot_data.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/uv.h>
#समावेश "boot.h"

अक्षर __bootdata(early_command_line)[COMMAND_LINE_SIZE];
काष्ठा ipl_parameter_block __bootdata_preserved(ipl_block);
पूर्णांक __bootdata_preserved(ipl_block_valid);
अचिन्हित पूर्णांक __bootdata_preserved(zlib_dfltcc_support) = ZLIB_DFLTCC_FULL;

अचिन्हित दीर्घ __bootdata(vदो_स्मृति_size) = VMALLOC_DEFAULT_SIZE;
पूर्णांक __bootdata(noexec_disabled);

अचिन्हित दीर्घ memory_limit;
पूर्णांक vदो_स्मृति_size_set;
पूर्णांक kaslr_enabled;

अटल अंतरभूत पूर्णांक __diag308(अचिन्हित दीर्घ subcode, व्योम *addr)
अणु
	रेजिस्टर अचिन्हित दीर्घ _addr यंत्र("0") = (अचिन्हित दीर्घ)addr;
	रेजिस्टर अचिन्हित दीर्घ _rc यंत्र("1") = 0;
	अचिन्हित दीर्घ reg1, reg2;
	psw_t old = S390_lowcore.program_new_psw;

	यंत्र अस्थिर(
		"	epsw	%0,%1\n"
		"	st	%0,%[psw_pgm]\n"
		"	st	%1,%[psw_pgm]+4\n"
		"	larl	%0,1f\n"
		"	stg	%0,%[psw_pgm]+8\n"
		"	diag	%[addr],%[subcode],0x308\n"
		"1:	nopr	%%r7\n"
		: "=&d" (reg1), "=&a" (reg2),
		  [psw_pgm] "=Q" (S390_lowcore.program_new_psw),
		  [addr] "+d" (_addr), "+d" (_rc)
		: [subcode] "d" (subcode)
		: "cc", "memory");
	S390_lowcore.program_new_psw = old;
	वापस _rc;
पूर्ण

व्योम store_ipl_parmblock(व्योम)
अणु
	पूर्णांक rc;

	rc = __diag308(DIAG308_STORE, &ipl_block);
	अगर (rc == DIAG308_RC_OK &&
	    ipl_block.hdr.version <= IPL_MAX_SUPPORTED_VERSION)
		ipl_block_valid = 1;
पूर्ण

bool is_ipl_block_dump(व्योम)
अणु
	अगर (ipl_block.pb0_hdr.pbt == IPL_PBT_FCP &&
	    ipl_block.fcp.opt == IPL_PB0_FCP_OPT_DUMP)
		वापस true;
	अगर (ipl_block.pb0_hdr.pbt == IPL_PBT_NVME &&
	    ipl_block.nvme.opt == IPL_PB0_NVME_OPT_DUMP)
		वापस true;
	वापस false;
पूर्ण

अटल माप_प्रकार scpdata_length(स्थिर u8 *buf, माप_प्रकार count)
अणु
	जबतक (count) अणु
		अगर (buf[count - 1] != '\0' && buf[count - 1] != ' ')
			अवरोध;
		count--;
	पूर्ण
	वापस count;
पूर्ण

अटल माप_प्रकार ipl_block_get_ascii_scpdata(अक्षर *dest, माप_प्रकार size,
					  स्थिर काष्ठा ipl_parameter_block *ipb)
अणु
	स्थिर __u8 *scp_data;
	__u32 scp_data_len;
	पूर्णांक has_lowerहाल;
	माप_प्रकार count = 0;
	माप_प्रकार i;

	चयन (ipb->pb0_hdr.pbt) अणु
	हाल IPL_PBT_FCP:
		scp_data_len = ipb->fcp.scp_data_len;
		scp_data = ipb->fcp.scp_data;
		अवरोध;
	हाल IPL_PBT_NVME:
		scp_data_len = ipb->nvme.scp_data_len;
		scp_data = ipb->nvme.scp_data;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	count = min(size - 1, scpdata_length(scp_data, scp_data_len));
	अगर (!count)
		जाओ out;

	has_lowerहाल = 0;
	क्रम (i = 0; i < count; i++) अणु
		अगर (!isascii(scp_data[i])) अणु
			count = 0;
			जाओ out;
		पूर्ण
		अगर (!has_lowerहाल && है_छोटा(scp_data[i]))
			has_lowerहाल = 1;
	पूर्ण

	अगर (has_lowerहाल)
		स_नकल(dest, scp_data, count);
	अन्यथा
		क्रम (i = 0; i < count; i++)
			dest[i] = छोटे(scp_data[i]);
out:
	dest[count] = '\0';
	वापस count;
पूर्ण

अटल व्योम append_ipl_block_parm(व्योम)
अणु
	अक्षर *parm, *delim;
	माप_प्रकार len, rc = 0;

	len = म_माप(early_command_line);

	delim = early_command_line + len;    /* '\0' अक्षरacter position */
	parm = early_command_line + len + 1; /* append right after '\0' */

	चयन (ipl_block.pb0_hdr.pbt) अणु
	हाल IPL_PBT_CCW:
		rc = ipl_block_get_ascii_vmparm(
			parm, COMMAND_LINE_SIZE - len - 1, &ipl_block);
		अवरोध;
	हाल IPL_PBT_FCP:
	हाल IPL_PBT_NVME:
		rc = ipl_block_get_ascii_scpdata(
			parm, COMMAND_LINE_SIZE - len - 1, &ipl_block);
		अवरोध;
	पूर्ण
	अगर (rc) अणु
		अगर (*parm == '=')
			स_हटाओ(early_command_line, parm + 1, rc);
		अन्यथा
			*delim = ' '; /* replace '\0' with space */
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक has_ebcdic_अक्षर(स्थिर अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; str[i]; i++)
		अगर (str[i] & 0x80)
			वापस 1;
	वापस 0;
पूर्ण

व्योम setup_boot_command_line(व्योम)
अणु
	COMMAND_LINE[ARCH_COMMAND_LINE_SIZE - 1] = 0;
	/* convert arch command line to ascii अगर necessary */
	अगर (has_ebcdic_अक्षर(COMMAND_LINE))
		EBCASC(COMMAND_LINE, ARCH_COMMAND_LINE_SIZE);
	/* copy arch command line */
	म_नकल(early_command_line, strim(COMMAND_LINE));

	/* append IPL PARM data to the boot command line */
	अगर (!is_prot_virt_guest() && ipl_block_valid)
		append_ipl_block_parm();
पूर्ण

अटल व्योम modअगरy_facility(अचिन्हित दीर्घ nr, bool clear)
अणु
	अगर (clear)
		__clear_facility(nr, S390_lowcore.stfle_fac_list);
	अन्यथा
		__set_facility(nr, S390_lowcore.stfle_fac_list);
पूर्ण

अटल व्योम check_cleared_facilities(व्योम)
अणु
	अचिन्हित दीर्घ als[] = अणु FACILITIES_ALS पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(als); i++) अणु
		अगर ((S390_lowcore.stfle_fac_list[i] & als[i]) != als[i]) अणु
			sclp_early_prपूर्णांकk("Warning: The Linux kernel requires facilities cleared via command line option\n");
			prपूर्णांक_missing_facilities();
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम modअगरy_fac_list(अक्षर *str)
अणु
	अचिन्हित दीर्घ val, endval;
	अक्षर *endp;
	bool clear;

	जबतक (*str) अणु
		clear = false;
		अगर (*str == '!') अणु
			clear = true;
			str++;
		पूर्ण
		val = simple_म_से_अदीर्घl(str, &endp, 0);
		अगर (str == endp)
			अवरोध;
		str = endp;
		अगर (*str == '-') अणु
			str++;
			endval = simple_म_से_अदीर्घl(str, &endp, 0);
			अगर (str == endp)
				अवरोध;
			str = endp;
			जबतक (val <= endval) अणु
				modअगरy_facility(val, clear);
				val++;
			पूर्ण
		पूर्ण अन्यथा अणु
			modअगरy_facility(val, clear);
		पूर्ण
		अगर (*str != ',')
			अवरोध;
		str++;
	पूर्ण
	check_cleared_facilities();
पूर्ण

अटल अक्षर command_line_buf[COMMAND_LINE_SIZE];
व्योम parse_boot_command_line(व्योम)
अणु
	अक्षर *param, *val;
	bool enabled;
	अक्षर *args;
	पूर्णांक rc;

	kaslr_enabled = IS_ENABLED(CONFIG_RANDOMIZE_BASE);
	args = म_नकल(command_line_buf, early_command_line);
	जबतक (*args) अणु
		args = next_arg(args, &param, &val);

		अगर (!म_भेद(param, "mem") && val)
			memory_limit = round_करोwn(memparse(val, शून्य), PAGE_SIZE);

		अगर (!म_भेद(param, "vmalloc") && val) अणु
			vदो_स्मृति_size = round_up(memparse(val, शून्य), PAGE_SIZE);
			vदो_स्मृति_size_set = 1;
		पूर्ण

		अगर (!म_भेद(param, "dfltcc") && val) अणु
			अगर (!म_भेद(val, "off"))
				zlib_dfltcc_support = ZLIB_DFLTCC_DISABLED;
			अन्यथा अगर (!म_भेद(val, "on"))
				zlib_dfltcc_support = ZLIB_DFLTCC_FULL;
			अन्यथा अगर (!म_भेद(val, "def_only"))
				zlib_dfltcc_support = ZLIB_DFLTCC_DEFLATE_ONLY;
			अन्यथा अगर (!म_भेद(val, "inf_only"))
				zlib_dfltcc_support = ZLIB_DFLTCC_INFLATE_ONLY;
			अन्यथा अगर (!म_भेद(val, "always"))
				zlib_dfltcc_support = ZLIB_DFLTCC_FULL_DEBUG;
		पूर्ण

		अगर (!म_भेद(param, "noexec")) अणु
			rc = kstrtobool(val, &enabled);
			अगर (!rc && !enabled)
				noexec_disabled = 1;
		पूर्ण

		अगर (!म_भेद(param, "facilities") && val)
			modअगरy_fac_list(val);

		अगर (!म_भेद(param, "nokaslr"))
			kaslr_enabled = 0;

#अगर IS_ENABLED(CONFIG_KVM)
		अगर (!म_भेद(param, "prot_virt")) अणु
			rc = kstrtobool(val, &enabled);
			अगर (!rc && enabled)
				prot_virt_host = 1;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
पूर्ण
