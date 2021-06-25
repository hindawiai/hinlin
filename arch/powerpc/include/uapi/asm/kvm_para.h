<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301, USA.
 *
 * Copyright IBM Corp. 2008
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#अगर_अघोषित _UAPI__POWERPC_KVM_PARA_H__
#घोषणा _UAPI__POWERPC_KVM_PARA_H__

#समावेश <linux/types.h>

/*
 * Additions to this काष्ठा must only occur at the end, and should be
 * accompanied by a KVM_MAGIC_FEAT flag to advertise that they are present
 * (albeit not necessarily relevant to the current target hardware platक्रमm).
 *
 * Struct fields are always 32 or 64 bit aligned, depending on them being 32
 * or 64 bit wide respectively.
 *
 * See Documentation/virt/kvm/ppc-pv.rst
 */
काष्ठा kvm_vcpu_arch_shared अणु
	__u64 scratch1;
	__u64 scratch2;
	__u64 scratch3;
	__u64 critical;		/* Guest may not get पूर्णांकerrupts अगर == r1 */
	__u64 sprg0;
	__u64 sprg1;
	__u64 sprg2;
	__u64 sprg3;
	__u64 srr0;
	__u64 srr1;
	__u64 dar;		/* dear on BookE */
	__u64 msr;
	__u32 dsisr;
	__u32 पूर्णांक_pending;	/* Tells the guest अगर we have an पूर्णांकerrupt */
	__u32 sr[16];
	__u32 mas0;
	__u32 mas1;
	__u64 mas7_3;
	__u64 mas2;
	__u32 mas4;
	__u32 mas6;
	__u32 esr;
	__u32 pir;

	/*
	 * SPRG4-7 are user-पढ़ोable, so we can only keep these consistent
	 * between the shared area and the real रेजिस्टरs when there's an
	 * पूर्णांकervening निकास to KVM.  This also applies to SPRG3 on some
	 * chips.
	 *
	 * This suffices क्रम access by guest userspace, since in PR-mode
	 * KVM, an निकास must occur when changing the guest's MSR[PR].
	 * If the guest kernel ग_लिखोs to SPRG3-7 via the shared area, it
	 * must also use the shared area क्रम पढ़ोing जबतक in kernel space.
	 */
	__u64 sprg4;
	__u64 sprg5;
	__u64 sprg6;
	__u64 sprg7;
पूर्ण;

#घोषणा KVM_SC_MAGIC_R0		0x4b564d21 /* "KVM!" */

#घोषणा KVM_HCALL_TOKEN(num)     _EV_HCALL_TOKEN(EV_KVM_VENDOR_ID, num)

#समावेश <यंत्र/epapr_hcalls.h>

#घोषणा KVM_FEATURE_MAGIC_PAGE	1

/* Magic page flags from host to guest */

#घोषणा KVM_MAGIC_FEAT_SR		(1 << 0)

/* MASn, ESR, PIR, and high SPRGs */
#घोषणा KVM_MAGIC_FEAT_MAS0_TO_SPRG7	(1 << 1)

/* Magic page flags from guest to host */

#घोषणा MAGIC_PAGE_FLAG_NOT_MAPPED_NX	(1 << 0)


#पूर्ण_अगर /* _UAPI__POWERPC_KVM_PARA_H__ */
