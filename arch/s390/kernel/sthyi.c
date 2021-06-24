<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * store hypervisor inक्रमmation inकाष्ठाion emulation functions.
 *
 * Copyright IBM Corp. 2016
 * Author(s): Janosch Frank <frankja@linux.vnet.ibm.com>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/sthyi.h>
#समावेश "entry.h"

#घोषणा DED_WEIGHT 0xffff
/*
 * CP and IFL as EBCDIC strings, SP/0x40 determines the end of string
 * as they are justअगरied with spaces.
 */
#घोषणा CP  0xc3d7404040404040UL
#घोषणा IFL 0xc9c6d34040404040UL

क्रमागत hdr_flags अणु
	HDR_NOT_LPAR   = 0x10,
	HDR_STACK_INCM = 0x20,
	HDR_STSI_UNAV  = 0x40,
	HDR_PERF_UNAV  = 0x80,
पूर्ण;

क्रमागत mac_validity अणु
	MAC_NAME_VLD = 0x20,
	MAC_ID_VLD   = 0x40,
	MAC_CNT_VLD  = 0x80,
पूर्ण;

क्रमागत par_flag अणु
	PAR_MT_EN = 0x80,
पूर्ण;

क्रमागत par_validity अणु
	PAR_GRP_VLD  = 0x08,
	PAR_ID_VLD   = 0x10,
	PAR_ABS_VLD  = 0x20,
	PAR_WGHT_VLD = 0x40,
	PAR_PCNT_VLD  = 0x80,
पूर्ण;

काष्ठा hdr_sctn अणु
	u8 infhflg1;
	u8 infhflg2; /* reserved */
	u8 infhval1; /* reserved */
	u8 infhval2; /* reserved */
	u8 reserved[3];
	u8 infhygct;
	u16 infhtotl;
	u16 infhdln;
	u16 infmoff;
	u16 infmlen;
	u16 infpoff;
	u16 infplen;
	u16 infhoff1;
	u16 infhlen1;
	u16 infgoff1;
	u16 infglen1;
	u16 infhoff2;
	u16 infhlen2;
	u16 infgoff2;
	u16 infglen2;
	u16 infhoff3;
	u16 infhlen3;
	u16 infgoff3;
	u16 infglen3;
	u8 reserved2[4];
पूर्ण __packed;

काष्ठा mac_sctn अणु
	u8 infmflg1; /* reserved */
	u8 infmflg2; /* reserved */
	u8 infmval1;
	u8 infmval2; /* reserved */
	u16 infmscps;
	u16 infmdcps;
	u16 infmsअगरl;
	u16 infmdअगरl;
	अक्षर infmname[8];
	अक्षर infmtype[4];
	अक्षर infmmanu[16];
	अक्षर infmseq[16];
	अक्षर infmpman[4];
	u8 reserved[4];
पूर्ण __packed;

काष्ठा par_sctn अणु
	u8 infpflg1;
	u8 infpflg2; /* reserved */
	u8 infpval1;
	u8 infpval2; /* reserved */
	u16 infppnum;
	u16 infpscps;
	u16 infpdcps;
	u16 infpsअगरl;
	u16 infpdअगरl;
	u16 reserved;
	अक्षर infppnam[8];
	u32 infpwbcp;
	u32 infpabcp;
	u32 infpwbअगर;
	u32 infpabअगर;
	अक्षर infplgnm[8];
	u32 infplgcp;
	u32 infplgअगर;
पूर्ण __packed;

काष्ठा sthyi_sctns अणु
	काष्ठा hdr_sctn hdr;
	काष्ठा mac_sctn mac;
	काष्ठा par_sctn par;
पूर्ण __packed;

काष्ठा cpu_inf अणु
	u64 lpar_cap;
	u64 lpar_grp_cap;
	u64 lpar_weight;
	u64 all_weight;
	पूर्णांक cpu_num_ded;
	पूर्णांक cpu_num_shd;
पूर्ण;

काष्ठा lpar_cpu_inf अणु
	काष्ठा cpu_inf cp;
	काष्ठा cpu_inf अगरl;
पूर्ण;

/*
 * STHYI requires extensive locking in the higher hypervisors
 * and is very computational/memory expensive. Thereक्रमe we
 * cache the retrieved data whose valid period is 1s.
 */
#घोषणा CACHE_VALID_JIFFIES	HZ

काष्ठा sthyi_info अणु
	व्योम *info;
	अचिन्हित दीर्घ end;
पूर्ण;

अटल DEFINE_MUTEX(sthyi_mutex);
अटल काष्ठा sthyi_info sthyi_cache;

अटल अंतरभूत u64 cpu_id(u8 ctidx, व्योम *diag224_buf)
अणु
	वापस *((u64 *)(diag224_buf + (ctidx + 1) * DIAG204_CPU_NAME_LEN));
पूर्ण

/*
 * Scales the cpu capping from the lpar range to the one expected in
 * sthyi data.
 *
 * diag204 reports a cap in hundredths of processor units.
 * z/VM's range क्रम one core is 0 - 0x10000.
 */
अटल u32 scale_cap(u32 in)
अणु
	वापस (0x10000 * in) / 100;
पूर्ण

अटल व्योम fill_hdr(काष्ठा sthyi_sctns *sctns)
अणु
	sctns->hdr.infhdln = माप(sctns->hdr);
	sctns->hdr.infmoff = माप(sctns->hdr);
	sctns->hdr.infmlen = माप(sctns->mac);
	sctns->hdr.infplen = माप(sctns->par);
	sctns->hdr.infpoff = sctns->hdr.infhdln + sctns->hdr.infmlen;
	sctns->hdr.infhtotl = sctns->hdr.infpoff + sctns->hdr.infplen;
पूर्ण

अटल व्योम fill_stsi_mac(काष्ठा sthyi_sctns *sctns,
			  काष्ठा sysinfo_1_1_1 *sysinfo)
अणु
	sclp_ocf_cpc_name_copy(sctns->mac.infmname);
	अगर (*(u64 *)sctns->mac.infmname != 0)
		sctns->mac.infmval1 |= MAC_NAME_VLD;

	अगर (stsi(sysinfo, 1, 1, 1))
		वापस;

	स_नकल(sctns->mac.infmtype, sysinfo->type, माप(sctns->mac.infmtype));
	स_नकल(sctns->mac.infmmanu, sysinfo->manufacturer, माप(sctns->mac.infmmanu));
	स_नकल(sctns->mac.infmpman, sysinfo->plant, माप(sctns->mac.infmpman));
	स_नकल(sctns->mac.infmseq, sysinfo->sequence, माप(sctns->mac.infmseq));

	sctns->mac.infmval1 |= MAC_ID_VLD;
पूर्ण

अटल व्योम fill_stsi_par(काष्ठा sthyi_sctns *sctns,
			  काष्ठा sysinfo_2_2_2 *sysinfo)
अणु
	अगर (stsi(sysinfo, 2, 2, 2))
		वापस;

	sctns->par.infppnum = sysinfo->lpar_number;
	स_नकल(sctns->par.infppnam, sysinfo->name, माप(sctns->par.infppnam));

	sctns->par.infpval1 |= PAR_ID_VLD;
पूर्ण

अटल व्योम fill_stsi(काष्ठा sthyi_sctns *sctns)
अणु
	व्योम *sysinfo;

	/* Errors are handled through the validity bits in the response. */
	sysinfo = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!sysinfo)
		वापस;

	fill_stsi_mac(sctns, sysinfo);
	fill_stsi_par(sctns, sysinfo);

	मुक्त_pages((अचिन्हित दीर्घ)sysinfo, 0);
पूर्ण

अटल व्योम fill_diag_mac(काष्ठा sthyi_sctns *sctns,
			  काष्ठा diag204_x_phys_block *block,
			  व्योम *diag224_buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < block->hdr.cpus; i++) अणु
		चयन (cpu_id(block->cpus[i].ctidx, diag224_buf)) अणु
		हाल CP:
			अगर (block->cpus[i].weight == DED_WEIGHT)
				sctns->mac.infmdcps++;
			अन्यथा
				sctns->mac.infmscps++;
			अवरोध;
		हाल IFL:
			अगर (block->cpus[i].weight == DED_WEIGHT)
				sctns->mac.infmdअगरl++;
			अन्यथा
				sctns->mac.infmsअगरl++;
			अवरोध;
		पूर्ण
	पूर्ण
	sctns->mac.infmval1 |= MAC_CNT_VLD;
पूर्ण

/* Returns a poपूर्णांकer to the the next partition block. */
अटल काष्ठा diag204_x_part_block *lpar_cpu_inf(काष्ठा lpar_cpu_inf *part_inf,
						 bool this_lpar,
						 व्योम *diag224_buf,
						 काष्ठा diag204_x_part_block *block)
अणु
	पूर्णांक i, capped = 0, weight_cp = 0, weight_अगरl = 0;
	काष्ठा cpu_inf *cpu_inf;

	क्रम (i = 0; i < block->hdr.rcpus; i++) अणु
		अगर (!(block->cpus[i].cflag & DIAG204_CPU_ONLINE))
			जारी;

		चयन (cpu_id(block->cpus[i].ctidx, diag224_buf)) अणु
		हाल CP:
			cpu_inf = &part_inf->cp;
			अगर (block->cpus[i].cur_weight < DED_WEIGHT)
				weight_cp |= block->cpus[i].cur_weight;
			अवरोध;
		हाल IFL:
			cpu_inf = &part_inf->अगरl;
			अगर (block->cpus[i].cur_weight < DED_WEIGHT)
				weight_अगरl |= block->cpus[i].cur_weight;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अगर (!this_lpar)
			जारी;

		capped |= block->cpus[i].cflag & DIAG204_CPU_CAPPED;
		cpu_inf->lpar_cap |= block->cpus[i].cpu_type_cap;
		cpu_inf->lpar_grp_cap |= block->cpus[i].group_cpu_type_cap;

		अगर (block->cpus[i].weight == DED_WEIGHT)
			cpu_inf->cpu_num_ded += 1;
		अन्यथा
			cpu_inf->cpu_num_shd += 1;
	पूर्ण

	अगर (this_lpar && capped) अणु
		part_inf->cp.lpar_weight = weight_cp;
		part_inf->अगरl.lpar_weight = weight_अगरl;
	पूर्ण
	part_inf->cp.all_weight += weight_cp;
	part_inf->अगरl.all_weight += weight_अगरl;
	वापस (काष्ठा diag204_x_part_block *)&block->cpus[i];
पूर्ण

अटल व्योम fill_diag(काष्ठा sthyi_sctns *sctns)
अणु
	पूर्णांक i, r, pages;
	bool this_lpar;
	व्योम *diag204_buf;
	व्योम *diag224_buf = शून्य;
	काष्ठा diag204_x_info_blk_hdr *ti_hdr;
	काष्ठा diag204_x_part_block *part_block;
	काष्ठा diag204_x_phys_block *phys_block;
	काष्ठा lpar_cpu_inf lpar_inf = अणुपूर्ण;

	/* Errors are handled through the validity bits in the response. */
	pages = diag204((अचिन्हित दीर्घ)DIAG204_SUBC_RSI |
			(अचिन्हित दीर्घ)DIAG204_INFO_EXT, 0, शून्य);
	अगर (pages <= 0)
		वापस;

	diag204_buf = vदो_स्मृति(array_size(pages, PAGE_SIZE));
	अगर (!diag204_buf)
		वापस;

	r = diag204((अचिन्हित दीर्घ)DIAG204_SUBC_STIB7 |
		    (अचिन्हित दीर्घ)DIAG204_INFO_EXT, pages, diag204_buf);
	अगर (r < 0)
		जाओ out;

	diag224_buf = (व्योम *)__get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!diag224_buf || diag224(diag224_buf))
		जाओ out;

	ti_hdr = diag204_buf;
	part_block = diag204_buf + माप(*ti_hdr);

	क्रम (i = 0; i < ti_hdr->npar; i++) अणु
		/*
		 * For the calling lpar we also need to get the cpu
		 * caps and weights. The समय inक्रमmation block header
		 * specअगरies the offset to the partition block of the
		 * caller lpar, so we know when we process its data.
		 */
		this_lpar = (व्योम *)part_block - diag204_buf == ti_hdr->this_part;
		part_block = lpar_cpu_inf(&lpar_inf, this_lpar, diag224_buf,
					  part_block);
	पूर्ण

	phys_block = (काष्ठा diag204_x_phys_block *)part_block;
	part_block = diag204_buf + ti_hdr->this_part;
	अगर (part_block->hdr.mtid)
		sctns->par.infpflg1 = PAR_MT_EN;

	sctns->par.infpval1 |= PAR_GRP_VLD;
	sctns->par.infplgcp = scale_cap(lpar_inf.cp.lpar_grp_cap);
	sctns->par.infplgअगर = scale_cap(lpar_inf.अगरl.lpar_grp_cap);
	स_नकल(sctns->par.infplgnm, part_block->hdr.hardware_group_name,
	       माप(sctns->par.infplgnm));

	sctns->par.infpscps = lpar_inf.cp.cpu_num_shd;
	sctns->par.infpdcps = lpar_inf.cp.cpu_num_ded;
	sctns->par.infpsअगरl = lpar_inf.अगरl.cpu_num_shd;
	sctns->par.infpdअगरl = lpar_inf.अगरl.cpu_num_ded;
	sctns->par.infpval1 |= PAR_PCNT_VLD;

	sctns->par.infpabcp = scale_cap(lpar_inf.cp.lpar_cap);
	sctns->par.infpabअगर = scale_cap(lpar_inf.अगरl.lpar_cap);
	sctns->par.infpval1 |= PAR_ABS_VLD;

	/*
	 * Everything below needs global perक्रमmance data to be
	 * meaningful.
	 */
	अगर (!(ti_hdr->flags & DIAG204_LPAR_PHYS_FLG)) अणु
		sctns->hdr.infhflg1 |= HDR_PERF_UNAV;
		जाओ out;
	पूर्ण

	fill_diag_mac(sctns, phys_block, diag224_buf);

	अगर (lpar_inf.cp.lpar_weight) अणु
		sctns->par.infpwbcp = sctns->mac.infmscps * 0x10000 *
			lpar_inf.cp.lpar_weight / lpar_inf.cp.all_weight;
	पूर्ण

	अगर (lpar_inf.अगरl.lpar_weight) अणु
		sctns->par.infpwbअगर = sctns->mac.infmsअगरl * 0x10000 *
			lpar_inf.अगरl.lpar_weight / lpar_inf.अगरl.all_weight;
	पूर्ण
	sctns->par.infpval1 |= PAR_WGHT_VLD;

out:
	मुक्त_page((अचिन्हित दीर्घ)diag224_buf);
	vमुक्त(diag204_buf);
पूर्ण

अटल पूर्णांक sthyi(u64 vaddr, u64 *rc)
अणु
	रेजिस्टर u64 code यंत्र("0") = 0;
	रेजिस्टर u64 addr यंत्र("2") = vaddr;
	रेजिस्टर u64 rcode यंत्र("3");
	पूर्णांक cc;

	यंत्र अस्थिर(
		".insn   rre,0xB2560000,%[code],%[addr]\n"
		"ipm     %[cc]\n"
		"srl     %[cc],28\n"
		: [cc] "=d" (cc), "=d" (rcode)
		: [code] "d" (code), [addr] "a" (addr)
		: "memory", "cc");
	*rc = rcode;
	वापस cc;
पूर्ण

अटल पूर्णांक fill_dst(व्योम *dst, u64 *rc)
अणु
	काष्ठा sthyi_sctns *sctns = (काष्ठा sthyi_sctns *)dst;

	/*
	 * If the facility is on, we करोn't want to emulate the inकाष्ठाion.
	 * We ask the hypervisor to provide the data.
	 */
	अगर (test_facility(74))
		वापस sthyi((u64)dst, rc);

	fill_hdr(sctns);
	fill_stsi(sctns);
	fill_diag(sctns);
	*rc = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sthyi_init_cache(व्योम)
अणु
	अगर (sthyi_cache.info)
		वापस 0;
	sthyi_cache.info = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!sthyi_cache.info)
		वापस -ENOMEM;
	sthyi_cache.end = jअगरfies - 1; /* expired */
	वापस 0;
पूर्ण

अटल पूर्णांक sthyi_update_cache(u64 *rc)
अणु
	पूर्णांक r;

	स_रखो(sthyi_cache.info, 0, PAGE_SIZE);
	r = fill_dst(sthyi_cache.info, rc);
	अगर (r)
		वापस r;
	sthyi_cache.end = jअगरfies + CACHE_VALID_JIFFIES;
	वापस r;
पूर्ण

/*
 * sthyi_fill - Fill page with data वापसed by the STHYI inकाष्ठाion
 *
 * @dst: Poपूर्णांकer to zeroed page
 * @rc:  Poपूर्णांकer क्रम storing the वापस code of the inकाष्ठाion
 *
 * Fills the destination with प्रणाली inक्रमmation वापसed by the STHYI
 * inकाष्ठाion. The data is generated by emulation or execution of STHYI,
 * अगर available. The वापस value is the condition code that would be
 * वापसed, the rc parameter is the वापस code which is passed in
 * रेजिस्टर R2 + 1.
 */
पूर्णांक sthyi_fill(व्योम *dst, u64 *rc)
अणु
	पूर्णांक r;

	mutex_lock(&sthyi_mutex);
	r = sthyi_init_cache();
	अगर (r)
		जाओ out;

	अगर (समय_is_beक्रमe_jअगरfies(sthyi_cache.end)) अणु
		/* cache expired */
		r = sthyi_update_cache(rc);
		अगर (r)
			जाओ out;
	पूर्ण
	*rc = 0;
	स_नकल(dst, sthyi_cache.info, PAGE_SIZE);
out:
	mutex_unlock(&sthyi_mutex);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(sthyi_fill);

SYSCALL_DEFINE4(s390_sthyi, अचिन्हित दीर्घ, function_code, व्योम __user *, buffer,
		u64 __user *, वापस_code, अचिन्हित दीर्घ, flags)
अणु
	u64 sthyi_rc;
	व्योम *info;
	पूर्णांक r;

	अगर (flags)
		वापस -EINVAL;
	अगर (function_code != STHYI_FC_CP_IFL_CAP)
		वापस -EOPNOTSUPP;
	info = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	r = sthyi_fill(info, &sthyi_rc);
	अगर (r < 0)
		जाओ out;
	अगर (वापस_code && put_user(sthyi_rc, वापस_code)) अणु
		r = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (copy_to_user(buffer, info, PAGE_SIZE))
		r = -EFAULT;
out:
	मुक्त_page((अचिन्हित दीर्घ)info);
	वापस r;
पूर्ण
