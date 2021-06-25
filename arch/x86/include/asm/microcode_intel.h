<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MICROCODE_INTEL_H
#घोषणा _ASM_X86_MICROCODE_INTEL_H

#समावेश <यंत्र/microcode.h>

काष्ठा microcode_header_पूर्णांकel अणु
	अचिन्हित पूर्णांक            hdrver;
	अचिन्हित पूर्णांक            rev;
	अचिन्हित पूर्णांक            date;
	अचिन्हित पूर्णांक            sig;
	अचिन्हित पूर्णांक            cksum;
	अचिन्हित पूर्णांक            ldrver;
	अचिन्हित पूर्णांक            pf;
	अचिन्हित पूर्णांक            datasize;
	अचिन्हित पूर्णांक            totalsize;
	अचिन्हित पूर्णांक            reserved[3];
पूर्ण;

काष्ठा microcode_पूर्णांकel अणु
	काष्ठा microcode_header_पूर्णांकel hdr;
	अचिन्हित पूर्णांक            bits[0];
पूर्ण;

/* microcode क्रमmat is extended from prescott processors */
काष्ठा extended_signature अणु
	अचिन्हित पूर्णांक            sig;
	अचिन्हित पूर्णांक            pf;
	अचिन्हित पूर्णांक            cksum;
पूर्ण;

काष्ठा extended_sigtable अणु
	अचिन्हित पूर्णांक            count;
	अचिन्हित पूर्णांक            cksum;
	अचिन्हित पूर्णांक            reserved[3];
	काष्ठा extended_signature sigs[0];
पूर्ण;

#घोषणा DEFAULT_UCODE_DATASIZE	(2000)
#घोषणा MC_HEADER_SIZE		(माप(काष्ठा microcode_header_पूर्णांकel))
#घोषणा DEFAULT_UCODE_TOTALSIZE (DEFAULT_UCODE_DATASIZE + MC_HEADER_SIZE)
#घोषणा EXT_HEADER_SIZE		(माप(काष्ठा extended_sigtable))
#घोषणा EXT_SIGNATURE_SIZE	(माप(काष्ठा extended_signature))

#घोषणा get_totalsize(mc) \
	(((काष्ठा microcode_पूर्णांकel *)mc)->hdr.datasize ? \
	 ((काष्ठा microcode_पूर्णांकel *)mc)->hdr.totalsize : \
	 DEFAULT_UCODE_TOTALSIZE)

#घोषणा get_datasize(mc) \
	(((काष्ठा microcode_पूर्णांकel *)mc)->hdr.datasize ? \
	 ((काष्ठा microcode_पूर्णांकel *)mc)->hdr.datasize : DEFAULT_UCODE_DATASIZE)

#घोषणा exttable_size(et) ((et)->count * EXT_SIGNATURE_SIZE + EXT_HEADER_SIZE)

अटल अंतरभूत u32 पूर्णांकel_get_microcode_revision(व्योम)
अणु
	u32 rev, dummy;

	native_wrmsrl(MSR_IA32_UCODE_REV, 0);

	/* As करोcumented in the SDM: Do a CPUID 1 here */
	native_cpuid_eax(1);

	/* get the current revision from MSR 0x8B */
	native_rdmsr(MSR_IA32_UCODE_REV, dummy, rev);

	वापस rev;
पूर्ण

#अगर_घोषित CONFIG_MICROCODE_INTEL
बाह्य व्योम __init load_ucode_पूर्णांकel_bsp(व्योम);
बाह्य व्योम load_ucode_पूर्णांकel_ap(व्योम);
बाह्य व्योम show_ucode_info_early(व्योम);
बाह्य पूर्णांक __init save_microcode_in_initrd_पूर्णांकel(व्योम);
व्योम reload_ucode_पूर्णांकel(व्योम);
#अन्यथा
अटल अंतरभूत __init व्योम load_ucode_पूर्णांकel_bsp(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम load_ucode_पूर्णांकel_ap(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम show_ucode_info_early(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक __init save_microcode_in_initrd_पूर्णांकel(व्योम) अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत व्योम reload_ucode_पूर्णांकel(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_MICROCODE_INTEL_H */
