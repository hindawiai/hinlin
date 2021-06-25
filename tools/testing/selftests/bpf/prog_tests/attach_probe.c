<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "test_attach_probe.skel.h"

#अगर defined(__घातerpc64__) && defined(_CALL_ELF) && _CALL_ELF == 2

#घोषणा OP_RT_RA_MASK   0xffff0000UL
#घोषणा LIS_R2          0x3c400000UL
#घोषणा ADDIS_R2_R12    0x3c4c0000UL
#घोषणा ADDI_R2_R2      0x38420000UL

अटल sमाप_प्रकार get_offset(sमाप_प्रकार addr, sमाप_प्रकार base)
अणु
	u32 *insn = (u32 *) addr;

	/*
	 * A PPC64 ABIv2 function may have a local and a global entry
	 * poपूर्णांक. We need to use the local entry poपूर्णांक when patching
	 * functions, so identअगरy and step over the global entry poपूर्णांक
	 * sequence.
	 *
	 * The global entry poपूर्णांक sequence is always of the क्रमm:
	 *
	 * addis r2,r12,XXXX
	 * addi  r2,r2,XXXX
	 *
	 * A linker optimisation may convert the addis to lis:
	 *
	 * lis   r2,XXXX
	 * addi  r2,r2,XXXX
	 */
	अगर ((((*insn & OP_RT_RA_MASK) == ADDIS_R2_R12) ||
	     ((*insn & OP_RT_RA_MASK) == LIS_R2)) &&
	    ((*(insn + 1) & OP_RT_RA_MASK) == ADDI_R2_R2))
		वापस (sमाप_प्रकार)(insn + 2) - base;
	अन्यथा
		वापस addr - base;
पूर्ण
#अन्यथा
#घोषणा get_offset(addr, base) (addr - base)
#पूर्ण_अगर

sमाप_प्रकार get_base_addr() अणु
	माप_प्रकार start, offset;
	अक्षर buf[256];
	खाता *f;

	f = ख_खोलो("/proc/self/maps", "r");
	अगर (!f)
		वापस -त्रुटि_सं;

	जबतक (ख_पूछो(f, "%zx-%*x %s %zx %*[^\न]\न",
		      &start, buf, &offset) == 3) अणु
		अगर (म_भेद(buf, "r-xp") == 0) अणु
			ख_बंद(f);
			वापस start - offset;
		पूर्ण
	पूर्ण

	ख_बंद(f);
	वापस -EINVAL;
पूर्ण

व्योम test_attach_probe(व्योम)
अणु
	पूर्णांक duration = 0;
	काष्ठा bpf_link *kprobe_link, *kretprobe_link;
	काष्ठा bpf_link *uprobe_link, *uretprobe_link;
	काष्ठा test_attach_probe* skel;
	माप_प्रकार uprobe_offset;
	sमाप_प्रकार base_addr;

	base_addr = get_base_addr();
	अगर (CHECK(base_addr < 0, "get_base_addr",
		  "failed to find base addr: %zd", base_addr))
		वापस;
	uprobe_offset = get_offset((माप_प्रकार)&get_base_addr, base_addr);

	skel = test_attach_probe__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;
	अगर (CHECK(!skel->bss, "check_bss", ".bss wasn't mmap()-ed\n"))
		जाओ cleanup;

	kprobe_link = bpf_program__attach_kprobe(skel->progs.handle_kprobe,
						 false /* retprobe */,
						 SYS_न_अंकOSLEEP_KPROBE_NAME);
	अगर (CHECK(IS_ERR(kprobe_link), "attach_kprobe",
		  "err %ld\n", PTR_ERR(kprobe_link)))
		जाओ cleanup;
	skel->links.handle_kprobe = kprobe_link;

	kretprobe_link = bpf_program__attach_kprobe(skel->progs.handle_kretprobe,
						    true /* retprobe */,
						    SYS_न_अंकOSLEEP_KPROBE_NAME);
	अगर (CHECK(IS_ERR(kretprobe_link), "attach_kretprobe",
		  "err %ld\n", PTR_ERR(kretprobe_link)))
		जाओ cleanup;
	skel->links.handle_kretprobe = kretprobe_link;

	uprobe_link = bpf_program__attach_uprobe(skel->progs.handle_uprobe,
						 false /* retprobe */,
						 0 /* self pid */,
						 "/proc/self/exe",
						 uprobe_offset);
	अगर (CHECK(IS_ERR(uprobe_link), "attach_uprobe",
		  "err %ld\n", PTR_ERR(uprobe_link)))
		जाओ cleanup;
	skel->links.handle_uprobe = uprobe_link;

	uretprobe_link = bpf_program__attach_uprobe(skel->progs.handle_uretprobe,
						    true /* retprobe */,
						    -1 /* any pid */,
						    "/proc/self/exe",
						    uprobe_offset);
	अगर (CHECK(IS_ERR(uretprobe_link), "attach_uretprobe",
		  "err %ld\n", PTR_ERR(uretprobe_link)))
		जाओ cleanup;
	skel->links.handle_uretprobe = uretprobe_link;

	/* trigger & validate kprobe && kretprobe */
	usleep(1);

	अगर (CHECK(skel->bss->kprobe_res != 1, "check_kprobe_res",
		  "wrong kprobe res: %d\n", skel->bss->kprobe_res))
		जाओ cleanup;
	अगर (CHECK(skel->bss->kretprobe_res != 2, "check_kretprobe_res",
		  "wrong kretprobe res: %d\n", skel->bss->kretprobe_res))
		जाओ cleanup;

	/* trigger & validate uprobe & uretprobe */
	get_base_addr();

	अगर (CHECK(skel->bss->uprobe_res != 3, "check_uprobe_res",
		  "wrong uprobe res: %d\n", skel->bss->uprobe_res))
		जाओ cleanup;
	अगर (CHECK(skel->bss->uretprobe_res != 4, "check_uretprobe_res",
		  "wrong uretprobe res: %d\n", skel->bss->uretprobe_res))
		जाओ cleanup;

cleanup:
	test_attach_probe__destroy(skel);
पूर्ण
