<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_target.c
 * CPP Access Width Decoder
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Francois H. Theron <francois.theron@netronome.com>
 */

#घोषणा pr_fmt(fmt)       "NFP target: " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश "nfp_cpp.h"

#समावेश "nfp6000/nfp6000.h"

#घोषणा P32 1
#घोषणा P64 2

/* This काष्ठाure ONLY includes items that can be करोne with a पढ़ो or ग_लिखो of
 * 32-bit or 64-bit words. All others are not listed.
 */

#घोषणा AT(_action, _token, _pull, _push)				\
	हाल NFP_CPP_ID(0, (_action), (_token)):			\
		वापस PUSHPULL((_pull), (_push))

अटल पूर्णांक target_rw(u32 cpp_id, पूर्णांक pp, पूर्णांक start, पूर्णांक len)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(0, 0,  0, pp);
	AT(1, 0, pp,  0);
	AT(NFP_CPP_ACTION_RW, 0, pp, pp);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_nbi_dma(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(0, 0,   0, P64);	/* ReadNbiDma */
	AT(1, 0,   P64, 0);	/* WriteNbiDma */
	AT(NFP_CPP_ACTION_RW, 0, P64, P64);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_nbi_stats(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(0, 0,   0, P32);	/* ReadNbiStats */
	AT(1, 0,   P32, 0);	/* WriteNbiStats */
	AT(NFP_CPP_ACTION_RW, 0, P32, P32);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_nbi_पंचांग(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(0, 0,   0, P64);	/* ReadNbiTM */
	AT(1, 0,   P64, 0);	/* WriteNbiTM */
	AT(NFP_CPP_ACTION_RW, 0, P64, P64);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_nbi_ppc(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(0, 0,   0, P64);	/* ReadNbiPreclassअगरier */
	AT(1, 0,   P64, 0);	/* WriteNbiPreclassअगरier */
	AT(NFP_CPP_ACTION_RW, 0, P64, P64);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_nbi(u32 cpp_id, u64 address)
अणु
	u64 rel_addr = address & 0x3fFFFF;

	अगर (rel_addr < (1 << 20))
		वापस nfp6000_nbi_dma(cpp_id);
	अगर (rel_addr < (2 << 20))
		वापस nfp6000_nbi_stats(cpp_id);
	अगर (rel_addr < (3 << 20))
		वापस nfp6000_nbi_पंचांग(cpp_id);
	वापस nfp6000_nbi_ppc(cpp_id);
पूर्ण

/* This काष्ठाure ONLY includes items that can be करोne with a पढ़ो or ग_लिखो of
 * 32-bit or 64-bit words. All others are not listed.
 */
अटल पूर्णांक nfp6000_mu_common(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(NFP_CPP_ACTION_RW, 0, P64, P64);	/* पढ़ो_be/ग_लिखो_be */
	AT(NFP_CPP_ACTION_RW, 1, P64, P64);	/* पढ़ो_le/ग_लिखो_le */
	AT(NFP_CPP_ACTION_RW, 2, P64, P64);	/* पढ़ो_swap_be/ग_लिखो_swap_be */
	AT(NFP_CPP_ACTION_RW, 3, P64, P64);	/* पढ़ो_swap_le/ग_लिखो_swap_le */
	AT(0, 0,   0, P64);	/* पढ़ो_be */
	AT(0, 1,   0, P64);	/* पढ़ो_le */
	AT(0, 2,   0, P64);	/* पढ़ो_swap_be */
	AT(0, 3,   0, P64);	/* पढ़ो_swap_le */
	AT(1, 0, P64,   0);	/* ग_लिखो_be */
	AT(1, 1, P64,   0);	/* ग_लिखो_le */
	AT(1, 2, P64,   0);	/* ग_लिखो_swap_be */
	AT(1, 3, P64,   0);	/* ग_लिखो_swap_le */
	AT(3, 0,   0, P32);	/* atomic_पढ़ो */
	AT(3, 2, P32,   0);	/* mask_compare_ग_लिखो */
	AT(4, 0, P32,   0);	/* atomic_ग_लिखो */
	AT(4, 2,   0,   0);	/* atomic_ग_लिखो_imm */
	AT(4, 3,   0, P32);	/* swap_imm */
	AT(5, 0, P32,   0);	/* set */
	AT(5, 3,   0, P32);	/* test_set_imm */
	AT(6, 0, P32,   0);	/* clr */
	AT(6, 3,   0, P32);	/* test_clr_imm */
	AT(7, 0, P32,   0);	/* add */
	AT(7, 3,   0, P32);	/* test_add_imm */
	AT(8, 0, P32,   0);	/* addsat */
	AT(8, 3,   0, P32);	/* test_subsat_imm */
	AT(9, 0, P32,   0);	/* sub */
	AT(9, 3,   0, P32);	/* test_sub_imm */
	AT(10, 0, P32,   0);	/* subsat */
	AT(10, 3,   0, P32);	/* test_subsat_imm */
	AT(13, 0,   0, P32);	/* microq128_get */
	AT(13, 1,   0, P32);	/* microq128_pop */
	AT(13, 2, P32,   0);	/* microq128_put */
	AT(15, 0, P32,   0);	/* xor */
	AT(15, 3,   0, P32);	/* test_xor_imm */
	AT(28, 0,   0, P32);	/* पढ़ो32_be */
	AT(28, 1,   0, P32);	/* पढ़ो32_le */
	AT(28, 2,   0, P32);	/* पढ़ो32_swap_be */
	AT(28, 3,   0, P32);	/* पढ़ो32_swap_le */
	AT(31, 0, P32,   0);	/* ग_लिखो32_be */
	AT(31, 1, P32,   0);	/* ग_लिखो32_le */
	AT(31, 2, P32,   0);	/* ग_लिखो32_swap_be */
	AT(31, 3, P32,   0);	/* ग_लिखो32_swap_le */
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_mu_cपंचांग(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(16, 1,   0, P32);	/* packet_पढ़ो_packet_status */
	AT(17, 1,   0, P32);	/* packet_credit_get */
	AT(17, 3,   0, P64);	/* packet_add_thपढ़ो */
	AT(18, 2,   0, P64);	/* packet_मुक्त_and_वापस_poपूर्णांकer */
	AT(18, 3,   0, P64);	/* packet_वापस_poपूर्णांकer */
	AT(21, 0,   0, P64);	/* pe_dma_to_memory_indirect */
	AT(21, 1,   0, P64);	/* pe_dma_to_memory_indirect_swap */
	AT(21, 2,   0, P64);	/* pe_dma_to_memory_indirect_मुक्त */
	AT(21, 3,   0, P64);	/* pe_dma_to_memory_indirect_मुक्त_swap */
	शेष:
		वापस nfp6000_mu_common(cpp_id);
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_mu_emu(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(18, 0,   0, P32);	/* पढ़ो_queue */
	AT(18, 1,   0, P32);	/* पढ़ो_queue_ring */
	AT(18, 2, P32,   0);	/* ग_लिखो_queue */
	AT(18, 3, P32,   0);	/* ग_लिखो_queue_ring */
	AT(20, 2, P32,   0);	/* journal */
	AT(21, 0,   0, P32);	/* get */
	AT(21, 1,   0, P32);	/* get_eop */
	AT(21, 2,   0, P32);	/* get_मुक्तly */
	AT(22, 0,   0, P32);	/* pop */
	AT(22, 1,   0, P32);	/* pop_eop */
	AT(22, 2,   0, P32);	/* pop_मुक्तly */
	शेष:
		वापस nfp6000_mu_common(cpp_id);
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_mu_imu(u32 cpp_id)
अणु
	वापस nfp6000_mu_common(cpp_id);
पूर्ण

अटल पूर्णांक nfp6000_mu(u32 cpp_id, u64 address)
अणु
	पूर्णांक pp;

	अगर (address < 0x2000000000ULL)
		pp = nfp6000_mu_cपंचांग(cpp_id);
	अन्यथा अगर (address < 0x8000000000ULL)
		pp = nfp6000_mu_emu(cpp_id);
	अन्यथा अगर (address < 0x9800000000ULL)
		pp = nfp6000_mu_cपंचांग(cpp_id);
	अन्यथा अगर (address < 0x9C00000000ULL)
		pp = nfp6000_mu_emu(cpp_id);
	अन्यथा अगर (address < 0xA000000000ULL)
		pp = nfp6000_mu_imu(cpp_id);
	अन्यथा
		pp = nfp6000_mu_cपंचांग(cpp_id);

	वापस pp;
पूर्ण

अटल पूर्णांक nfp6000_ila(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(0, 1,   0, P32);	/* पढ़ो_check_error */
	AT(2, 0,   0, P32);	/* पढ़ो_पूर्णांक */
	AT(3, 0, P32,   0);	/* ग_लिखो_पूर्णांक */
	शेष:
		वापस target_rw(cpp_id, P32, 48, 4);
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_pci(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(2, 0,   0, P32);
	AT(3, 0, P32,   0);
	शेष:
		वापस target_rw(cpp_id, P32, 4, 4);
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_crypto(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(2, 0, P64,   0);
	शेष:
		वापस target_rw(cpp_id, P64, 12, 4);
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_cap_xpb(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(0, 1,   0, P32); /* RingGet */
	AT(0, 2, P32,   0); /* Interthपढ़ो Signal */
	AT(1, 1, P32,   0); /* RingPut */
	AT(1, 2, P32,   0); /* CTNNWr */
	AT(2, 0,   0, P32); /* ReflectRd, संकेत none */
	AT(2, 1,   0, P32); /* ReflectRd, संकेत self */
	AT(2, 2,   0, P32); /* ReflectRd, संकेत remote */
	AT(2, 3,   0, P32); /* ReflectRd, संकेत both */
	AT(3, 0, P32,   0); /* ReflectWr, संकेत none */
	AT(3, 1, P32,   0); /* ReflectWr, संकेत self */
	AT(3, 2, P32,   0); /* ReflectWr, संकेत remote */
	AT(3, 3, P32,   0); /* ReflectWr, संकेत both */
	AT(NFP_CPP_ACTION_RW, 1, P32, P32);
	शेष:
		वापस target_rw(cpp_id, P32, 1, 63);
	पूर्ण
पूर्ण

अटल पूर्णांक nfp6000_cls(u32 cpp_id)
अणु
	चयन (cpp_id & NFP_CPP_ID(0, ~0, ~0)) अणु
	AT(0, 3, P32,  0); /* xor */
	AT(2, 0, P32,  0); /* set */
	AT(2, 1, P32,  0); /* clr */
	AT(4, 0, P32,  0); /* add */
	AT(4, 1, P32,  0); /* add64 */
	AT(6, 0, P32,  0); /* sub */
	AT(6, 1, P32,  0); /* sub64 */
	AT(6, 2, P32,  0); /* subsat */
	AT(8, 2, P32,  0); /* hash_mask */
	AT(8, 3, P32,  0); /* hash_clear */
	AT(9, 0,  0, P32); /* ring_get */
	AT(9, 1,  0, P32); /* ring_pop */
	AT(9, 2,  0, P32); /* ring_get_मुक्तly */
	AT(9, 3,  0, P32); /* ring_pop_मुक्तly */
	AT(10, 0, P32,  0); /* ring_put */
	AT(10, 2, P32,  0); /* ring_journal */
	AT(14, 0,  P32, 0); /* reflect_ग_लिखो_sig_local */
	AT(15, 1,  0, P32); /* reflect_पढ़ो_sig_local */
	AT(17, 2, P32,  0); /* statisic */
	AT(24, 0,  0, P32); /* ring_पढ़ो */
	AT(24, 1, P32,  0); /* ring_ग_लिखो */
	AT(25, 0,  0, P32); /* ring_workq_add_thपढ़ो */
	AT(25, 1, P32,  0); /* ring_workq_add_work */
	शेष:
		वापस target_rw(cpp_id, P32, 0, 64);
	पूर्ण
पूर्ण

पूर्णांक nfp_target_pushpull(u32 cpp_id, u64 address)
अणु
	चयन (NFP_CPP_ID_TARGET_of(cpp_id)) अणु
	हाल NFP_CPP_TARGET_NBI:
		वापस nfp6000_nbi(cpp_id, address);
	हाल NFP_CPP_TARGET_QDR:
		वापस target_rw(cpp_id, P32, 24, 4);
	हाल NFP_CPP_TARGET_ILA:
		वापस nfp6000_ila(cpp_id);
	हाल NFP_CPP_TARGET_MU:
		वापस nfp6000_mu(cpp_id, address);
	हाल NFP_CPP_TARGET_PCIE:
		वापस nfp6000_pci(cpp_id);
	हाल NFP_CPP_TARGET_ARM:
		अगर (address < 0x10000)
			वापस target_rw(cpp_id, P64, 1, 1);
		अन्यथा
			वापस target_rw(cpp_id, P32, 1, 1);
	हाल NFP_CPP_TARGET_CRYPTO:
		वापस nfp6000_crypto(cpp_id);
	हाल NFP_CPP_TARGET_CT_XPB:
		वापस nfp6000_cap_xpb(cpp_id);
	हाल NFP_CPP_TARGET_CLS:
		वापस nfp6000_cls(cpp_id);
	हाल 0:
		वापस target_rw(cpp_id, P32, 4, 4);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#अघोषित AT
#अघोषित P32
#अघोषित P64

/* All magic NFP-6xxx IMB 'mode' numbers here are from:
 * Databook (1 August 2013)
 * - System Overview and Connectivity
 * -- Internal Connectivity
 * --- Distributed Switch Fabric - Command Push/Pull (DSF-CPP) Bus
 * ---- CPP addressing
 * ----- Table 3.6. CPP Address Translation Mode Commands
 */

#घोषणा _NIC_NFP6000_MU_LOCALITY_सूचीECT     2

अटल पूर्णांक nfp_decode_basic(u64 addr, पूर्णांक *dest_island, पूर्णांक cpp_tgt,
			    पूर्णांक mode, bool addr40, पूर्णांक isld1, पूर्णांक isld0)
अणु
	पूर्णांक iid_lsb, idx_lsb;

	/* This function करोesn't handle MU or CTXBP */
	अगर (cpp_tgt == NFP_CPP_TARGET_MU || cpp_tgt == NFP_CPP_TARGET_CT_XPB)
		वापस -EINVAL;

	चयन (mode) अणु
	हाल 0:
		/* For VQDR, in this mode क्रम 32-bit addressing
		 * it would be islands 0, 16, 32 and 48 depending on channel
		 * and upper address bits.
		 * Since those are not all valid islands, most decode
		 * हालs would result in bad island IDs, but we करो them
		 * anyway since this is decoding an address that is alपढ़ोy
		 * assumed to be used as-is to get to sram.
		 */
		iid_lsb = addr40 ? 34 : 26;
		*dest_island = (addr >> iid_lsb) & 0x3F;
		वापस 0;
	हाल 1:
		/* For VQDR 32-bit, this would decode as:
		 * Channel 0: island#0
		 * Channel 1: island#0
		 * Channel 2: island#1
		 * Channel 3: island#1
		 * That would be valid as दीर्घ as both islands
		 * have VQDR. Let's allow this.
		 */
		idx_lsb = addr40 ? 39 : 31;
		अगर (addr & BIT_ULL(idx_lsb))
			*dest_island = isld1;
		अन्यथा
			*dest_island = isld0;

		वापस 0;
	हाल 2:
		/* For VQDR 32-bit:
		 * Channel 0: (island#0 | 0)
		 * Channel 1: (island#0 | 1)
		 * Channel 2: (island#1 | 0)
		 * Channel 3: (island#1 | 1)
		 *
		 * Make sure we compare against isldN values
		 * by clearing the LSB.
		 * This is what the silicon करोes.
		 */
		isld0 &= ~1;
		isld1 &= ~1;

		idx_lsb = addr40 ? 39 : 31;
		iid_lsb = idx_lsb - 1;

		अगर (addr & BIT_ULL(idx_lsb))
			*dest_island = isld1 | (पूर्णांक)((addr >> iid_lsb) & 1);
		अन्यथा
			*dest_island = isld0 | (पूर्णांक)((addr >> iid_lsb) & 1);

		वापस 0;
	हाल 3:
		/* In this mode the data address starts to affect the island ID
		 * so rather not allow it. In some really specअगरic हाल
		 * one could use this to send the upper half of the
		 * VQDR channel to another MU, but this is getting very
		 * specअगरic.
		 * However, as above क्रम mode 0, this is the decoder
		 * and the caller should validate the resulting IID.
		 * This blindly करोes what the silicon would करो.
		 */
		isld0 &= ~3;
		isld1 &= ~3;

		idx_lsb = addr40 ? 39 : 31;
		iid_lsb = idx_lsb - 2;

		अगर (addr & BIT_ULL(idx_lsb))
			*dest_island = isld1 | (पूर्णांक)((addr >> iid_lsb) & 3);
		अन्यथा
			*dest_island = isld0 | (पूर्णांक)((addr >> iid_lsb) & 3);

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp_encode_basic_qdr(u64 addr, पूर्णांक dest_island, पूर्णांक cpp_tgt,
				पूर्णांक mode, bool addr40, पूर्णांक isld1, पूर्णांक isld0)
अणु
	पूर्णांक v, ret;

	/* Full Island ID and channel bits overlap? */
	ret = nfp_decode_basic(addr, &v, cpp_tgt, mode, addr40, isld1, isld0);
	अगर (ret)
		वापस ret;

	/* The current address won't go where expected? */
	अगर (dest_island != -1 && dest_island != v)
		वापस -EINVAL;

	/* If dest_island was -1, we करोn't care where it goes. */
	वापस 0;
पूर्ण

/* Try each option, take first one that fits.
 * Not sure अगर we would want to करो some smarter
 * searching and prefer 0 or non-0 island IDs.
 */
अटल पूर्णांक nfp_encode_basic_search(u64 *addr, पूर्णांक dest_island, पूर्णांक *isld,
				   पूर्णांक iid_lsb, पूर्णांक idx_lsb, पूर्णांक v_max)
अणु
	पूर्णांक i, v;

	क्रम (i = 0; i < 2; i++)
		क्रम (v = 0; v < v_max; v++) अणु
			अगर (dest_island != (isld[i] | v))
				जारी;

			*addr &= ~GENMASK_ULL(idx_lsb, iid_lsb);
			*addr |= ((u64)i << idx_lsb);
			*addr |= ((u64)v << iid_lsb);
			वापस 0;
		पूर्ण

	वापस -ENODEV;
पूर्ण

/* For VQDR, we may not modअगरy the Channel bits, which might overlap
 *  with the Index bit. When it करोes, we need to ensure that isld0 == isld1.
 */
अटल पूर्णांक nfp_encode_basic(u64 *addr, पूर्णांक dest_island, पूर्णांक cpp_tgt,
			    पूर्णांक mode, bool addr40, पूर्णांक isld1, पूर्णांक isld0)
अणु
	पूर्णांक iid_lsb, idx_lsb;
	पूर्णांक isld[2];
	u64 v64;

	isld[0] = isld0;
	isld[1] = isld1;

	/* This function करोesn't handle MU or CTXBP */
	अगर (cpp_tgt == NFP_CPP_TARGET_MU || cpp_tgt == NFP_CPP_TARGET_CT_XPB)
		वापस -EINVAL;

	चयन (mode) अणु
	हाल 0:
		अगर (cpp_tgt == NFP_CPP_TARGET_QDR && !addr40)
			/* In this specअगरic mode we'd rather not modअगरy
			 * the address but we can verअगरy अगर the existing
			 * contents will poपूर्णांक to a valid island.
			 */
			वापस nfp_encode_basic_qdr(*addr, cpp_tgt, dest_island,
						    mode, addr40, isld1, isld0);

		iid_lsb = addr40 ? 34 : 26;
		/* <39:34> or <31:26> */
		v64 = GENMASK_ULL(iid_lsb + 5, iid_lsb);
		*addr &= ~v64;
		*addr |= ((u64)dest_island << iid_lsb) & v64;
		वापस 0;
	हाल 1:
		अगर (cpp_tgt == NFP_CPP_TARGET_QDR && !addr40)
			वापस nfp_encode_basic_qdr(*addr, cpp_tgt, dest_island,
						    mode, addr40, isld1, isld0);

		idx_lsb = addr40 ? 39 : 31;
		अगर (dest_island == isld0) अणु
			/* Only need to clear the Index bit */
			*addr &= ~BIT_ULL(idx_lsb);
			वापस 0;
		पूर्ण

		अगर (dest_island == isld1) अणु
			/* Only need to set the Index bit */
			*addr |= BIT_ULL(idx_lsb);
			वापस 0;
		पूर्ण

		वापस -ENODEV;
	हाल 2:
		/* iid<0> = addr<30> = channel<0>
		 * channel<1> = addr<31> = Index
		 */
		अगर (cpp_tgt == NFP_CPP_TARGET_QDR && !addr40)
			/* Special हाल where we allow channel bits to
			 * be set beक्रमe hand and with them select an island.
			 * So we need to confirm that it's at least plausible.
			 */
			वापस nfp_encode_basic_qdr(*addr, cpp_tgt, dest_island,
						    mode, addr40, isld1, isld0);

		/* Make sure we compare against isldN values
		 * by clearing the LSB.
		 * This is what the silicon करोes.
		 */
		isld[0] &= ~1;
		isld[1] &= ~1;

		idx_lsb = addr40 ? 39 : 31;
		iid_lsb = idx_lsb - 1;

		वापस nfp_encode_basic_search(addr, dest_island, isld,
					       iid_lsb, idx_lsb, 2);
	हाल 3:
		अगर (cpp_tgt == NFP_CPP_TARGET_QDR && !addr40)
			/* iid<0> = addr<29> = data
			 * iid<1> = addr<30> = channel<0>
			 * channel<1> = addr<31> = Index
			 */
			वापस nfp_encode_basic_qdr(*addr, cpp_tgt, dest_island,
						    mode, addr40, isld1, isld0);

		isld[0] &= ~3;
		isld[1] &= ~3;

		idx_lsb = addr40 ? 39 : 31;
		iid_lsb = idx_lsb - 2;

		वापस nfp_encode_basic_search(addr, dest_island, isld,
					       iid_lsb, idx_lsb, 4);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp_encode_mu(u64 *addr, पूर्णांक dest_island, पूर्णांक mode,
			 bool addr40, पूर्णांक isld1, पूर्णांक isld0)
अणु
	पूर्णांक iid_lsb, idx_lsb, locality_lsb;
	पूर्णांक isld[2];
	u64 v64;
	पूर्णांक da;

	isld[0] = isld0;
	isld[1] = isld1;
	locality_lsb = nfp_cppat_mu_locality_lsb(mode, addr40);

	अगर (((*addr >> locality_lsb) & 3) == _NIC_NFP6000_MU_LOCALITY_सूचीECT)
		da = 1;
	अन्यथा
		da = 0;

	चयन (mode) अणु
	हाल 0:
		iid_lsb = addr40 ? 32 : 24;
		v64 = GENMASK_ULL(iid_lsb + 5, iid_lsb);
		*addr &= ~v64;
		*addr |= (((u64)dest_island) << iid_lsb) & v64;
		वापस 0;
	हाल 1:
		अगर (da) अणु
			iid_lsb = addr40 ? 32 : 24;
			v64 = GENMASK_ULL(iid_lsb + 5, iid_lsb);
			*addr &= ~v64;
			*addr |= (((u64)dest_island) << iid_lsb) & v64;
			वापस 0;
		पूर्ण

		idx_lsb = addr40 ? 37 : 29;
		अगर (dest_island == isld0) अणु
			*addr &= ~BIT_ULL(idx_lsb);
			वापस 0;
		पूर्ण

		अगर (dest_island == isld1) अणु
			*addr |= BIT_ULL(idx_lsb);
			वापस 0;
		पूर्ण

		वापस -ENODEV;
	हाल 2:
		अगर (da) अणु
			iid_lsb = addr40 ? 32 : 24;
			v64 = GENMASK_ULL(iid_lsb + 5, iid_lsb);
			*addr &= ~v64;
			*addr |= (((u64)dest_island) << iid_lsb) & v64;
			वापस 0;
		पूर्ण

		/* Make sure we compare against isldN values
		 * by clearing the LSB.
		 * This is what the silicon करोes.
		 */
		isld[0] &= ~1;
		isld[1] &= ~1;

		idx_lsb = addr40 ? 37 : 29;
		iid_lsb = idx_lsb - 1;

		वापस nfp_encode_basic_search(addr, dest_island, isld,
					       iid_lsb, idx_lsb, 2);
	हाल 3:
		/* Only the EMU will use 40 bit addressing. Silently
		 * set the direct locality bit क्रम everyone अन्यथा.
		 * The SDK toolchain uses dest_island <= 0 to test
		 * क्रम atypical address encodings to support access
		 * to local-island CTM with a 32-but address (high-locality
		 * is effewctively ignored and just used क्रम
		 * routing to island #0).
		 */
		अगर (dest_island > 0 && (dest_island < 24 || dest_island > 26)) अणु
			*addr |= ((u64)_NIC_NFP6000_MU_LOCALITY_सूचीECT)
							<< locality_lsb;
			da = 1;
		पूर्ण

		अगर (da) अणु
			iid_lsb = addr40 ? 32 : 24;
			v64 = GENMASK_ULL(iid_lsb + 5, iid_lsb);
			*addr &= ~v64;
			*addr |= (((u64)dest_island) << iid_lsb) & v64;
			वापस 0;
		पूर्ण

		isld[0] &= ~3;
		isld[1] &= ~3;

		idx_lsb = addr40 ? 37 : 29;
		iid_lsb = idx_lsb - 2;

		वापस nfp_encode_basic_search(addr, dest_island, isld,
					       iid_lsb, idx_lsb, 4);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp_cppat_addr_encode(u64 *addr, पूर्णांक dest_island, पूर्णांक cpp_tgt,
				 पूर्णांक mode, bool addr40, पूर्णांक isld1, पूर्णांक isld0)
अणु
	चयन (cpp_tgt) अणु
	हाल NFP_CPP_TARGET_NBI:
	हाल NFP_CPP_TARGET_QDR:
	हाल NFP_CPP_TARGET_ILA:
	हाल NFP_CPP_TARGET_PCIE:
	हाल NFP_CPP_TARGET_ARM:
	हाल NFP_CPP_TARGET_CRYPTO:
	हाल NFP_CPP_TARGET_CLS:
		वापस nfp_encode_basic(addr, dest_island, cpp_tgt, mode,
					addr40, isld1, isld0);

	हाल NFP_CPP_TARGET_MU:
		वापस nfp_encode_mu(addr, dest_island, mode,
				     addr40, isld1, isld0);

	हाल NFP_CPP_TARGET_CT_XPB:
		अगर (mode != 1 || addr40)
			वापस -EINVAL;
		*addr &= ~GENMASK_ULL(29, 24);
		*addr |= ((u64)dest_island << 24) & GENMASK_ULL(29, 24);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक nfp_target_cpp(u32 cpp_island_id, u64 cpp_island_address,
		   u32 *cpp_target_id, u64 *cpp_target_address,
		   स्थिर u32 *imb_table)
अणु
	स्थिर पूर्णांक island = NFP_CPP_ID_ISLAND_of(cpp_island_id);
	स्थिर पूर्णांक target = NFP_CPP_ID_TARGET_of(cpp_island_id);
	u32 imb;
	पूर्णांक err;

	अगर (target < 0 || target >= 16) अणु
		pr_err("Invalid CPP target: %d\n", target);
		वापस -EINVAL;
	पूर्ण

	अगर (island == 0) अणु
		/* Alपढ़ोy translated */
		*cpp_target_id = cpp_island_id;
		*cpp_target_address = cpp_island_address;
		वापस 0;
	पूर्ण

	/* CPP + Island only allowed on प्रणालीs with IMB tables */
	अगर (!imb_table)
		वापस -EINVAL;

	imb = imb_table[target];

	*cpp_target_address = cpp_island_address;
	err = nfp_cppat_addr_encode(cpp_target_address, island, target,
				    ((imb >> 13) & 7), ((imb >> 12) & 1),
				    ((imb >> 6)  & 0x3f), ((imb >> 0)  & 0x3f));
	अगर (err) अणु
		pr_err("Can't encode CPP address: %d\n", err);
		वापस err;
	पूर्ण

	*cpp_target_id = NFP_CPP_ID(target,
				    NFP_CPP_ID_ACTION_of(cpp_island_id),
				    NFP_CPP_ID_TOKEN_of(cpp_island_id));

	वापस 0;
पूर्ण
