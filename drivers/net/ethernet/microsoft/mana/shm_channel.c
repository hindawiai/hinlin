<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2021, Microsoft Corporation. */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>

#समावेश "shm_channel.h"

#घोषणा PAGE_FRAME_L48_WIDTH_BYTES 6
#घोषणा PAGE_FRAME_L48_WIDTH_BITS (PAGE_FRAME_L48_WIDTH_BYTES * 8)
#घोषणा PAGE_FRAME_L48_MASK 0x0000FFFFFFFFFFFF
#घोषणा PAGE_FRAME_H4_WIDTH_BITS 4
#घोषणा VECTOR_MASK 0xFFFF
#घोषणा SHMEM_VF_RESET_STATE ((u32)-1)

#घोषणा SMC_MSG_TYPE_ESTABLISH_HWC 1
#घोषणा SMC_MSG_TYPE_ESTABLISH_HWC_VERSION 0

#घोषणा SMC_MSG_TYPE_DESTROY_HWC 2
#घोषणा SMC_MSG_TYPE_DESTROY_HWC_VERSION 0

#घोषणा SMC_MSG_सूचीECTION_REQUEST 0
#घोषणा SMC_MSG_सूचीECTION_RESPONSE 1

/* Structures labeled with "HW DATA" are exchanged with the hardware. All of
 * them are naturally aligned and hence करोn't need __packed.
 */

/* Shared memory channel protocol header
 *
 * msg_type: set on request and response; response matches request.
 * msg_version: newer PF ग_लिखोs back older response (matching request)
 *  older PF acts on latest version known and sets that version in result
 *  (less than request).
 * direction: 0 क्रम request, VF->PF; 1 क्रम response, PF->VF.
 * status: 0 on request,
 *   operation result on response (success = 0, failure = 1 or greater).
 * reset_vf: If set on either establish or destroy request, indicates perक्रमm
 *  FLR beक्रमe/after the operation.
 * owner_is_pf: 1 indicates PF owned, 0 indicates VF owned.
 */
जोड़ smc_proto_hdr अणु
	u32 as_uपूर्णांक32;

	काष्ठा अणु
		u8 msg_type	: 3;
		u8 msg_version	: 3;
		u8 reserved_1	: 1;
		u8 direction	: 1;

		u8 status;

		u8 reserved_2;

		u8 reset_vf	: 1;
		u8 reserved_3	: 6;
		u8 owner_is_pf	: 1;
	पूर्ण;
पूर्ण; /* HW DATA */

#घोषणा SMC_APERTURE_BITS 256
#घोषणा SMC_BASIC_UNIT (माप(u32))
#घोषणा SMC_APERTURE_DWORDS (SMC_APERTURE_BITS / (SMC_BASIC_UNIT * 8))
#घोषणा SMC_LAST_DWORD (SMC_APERTURE_DWORDS - 1)

अटल पूर्णांक mana_smc_poll_रेजिस्टर(व्योम __iomem *base, bool reset)
अणु
	व्योम __iomem *ptr = base + SMC_LAST_DWORD * SMC_BASIC_UNIT;
	u32 last_dword;
	पूर्णांक i;

	/* Poll the hardware क्रम the ownership bit. This should be pretty fast,
	 * but let's करो it in a loop just in हाल the hardware or the PF
	 * driver are temporarily busy.
	 */
	क्रम (i = 0; i < 20 * 1000; i++)  अणु
		last_dword = पढ़ोl(ptr);

		/* shmem पढ़ोs as 0xFFFFFFFF in the reset हाल */
		अगर (reset && last_dword == SHMEM_VF_RESET_STATE)
			वापस 0;

		/* If bit_31 is set, the PF currently owns the SMC. */
		अगर (!(last_dword & BIT(31)))
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक mana_smc_पढ़ो_response(काष्ठा shm_channel *sc, u32 msg_type,
				  u32 msg_version, bool reset_vf)
अणु
	व्योम __iomem *base = sc->base;
	जोड़ smc_proto_hdr hdr;
	पूर्णांक err;

	/* Wait क्रम PF to respond. */
	err = mana_smc_poll_रेजिस्टर(base, reset_vf);
	अगर (err)
		वापस err;

	hdr.as_uपूर्णांक32 = पढ़ोl(base + SMC_LAST_DWORD * SMC_BASIC_UNIT);

	अगर (reset_vf && hdr.as_uपूर्णांक32 == SHMEM_VF_RESET_STATE)
		वापस 0;

	/* Validate protocol fields from the PF driver */
	अगर (hdr.msg_type != msg_type || hdr.msg_version > msg_version ||
	    hdr.direction != SMC_MSG_सूचीECTION_RESPONSE) अणु
		dev_err(sc->dev, "Wrong SMC response 0x%x, type=%d, ver=%d\n",
			hdr.as_uपूर्णांक32, msg_type, msg_version);
		वापस -EPROTO;
	पूर्ण

	/* Validate the operation result */
	अगर (hdr.status != 0) अणु
		dev_err(sc->dev, "SMC operation failed: 0x%x\n", hdr.status);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mana_smc_init(काष्ठा shm_channel *sc, काष्ठा device *dev,
		   व्योम __iomem *base)
अणु
	sc->dev = dev;
	sc->base = base;
पूर्ण

पूर्णांक mana_smc_setup_hwc(काष्ठा shm_channel *sc, bool reset_vf, u64 eq_addr,
		       u64 cq_addr, u64 rq_addr, u64 sq_addr,
		       u32 eq_msix_index)
अणु
	जोड़ smc_proto_hdr *hdr;
	u16 all_addr_h4bits = 0;
	u16 frame_addr_seq = 0;
	u64 frame_addr = 0;
	u8 shm_buf[32];
	u64 *shmem;
	u32 *dword;
	u8 *ptr;
	पूर्णांक err;
	पूर्णांक i;

	/* Ensure VF alपढ़ोy has possession of shared memory */
	err = mana_smc_poll_रेजिस्टर(sc->base, false);
	अगर (err) अणु
		dev_err(sc->dev, "Timeout when setting up HWC: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!PAGE_ALIGNED(eq_addr) || !PAGE_ALIGNED(cq_addr) ||
	    !PAGE_ALIGNED(rq_addr) || !PAGE_ALIGNED(sq_addr))
		वापस -EINVAL;

	अगर ((eq_msix_index & VECTOR_MASK) != eq_msix_index)
		वापस -EINVAL;

	/* Scheme क्रम packing four addresses and extra info पूर्णांकo 256 bits.
	 *
	 * Addresses must be page frame aligned, so only frame address bits
	 * are transferred.
	 *
	 * 52-bit frame addresses are split पूर्णांकo the lower 48 bits and upper
	 * 4 bits. Lower 48 bits of 4 address are written sequentially from
	 * the start of the 256-bit shared memory region followed by 16 bits
	 * containing the upper 4 bits of the 4 addresses in sequence.
	 *
	 * A 16 bit EQ vector number fills out the next-to-last 32-bit dword.
	 *
	 * The final 32-bit dword is used क्रम protocol control inक्रमmation as
	 * defined in smc_proto_hdr.
	 */

	स_रखो(shm_buf, 0, माप(shm_buf));
	ptr = shm_buf;

	/* EQ addr: low 48 bits of frame address */
	shmem = (u64 *)ptr;
	frame_addr = PHYS_PFN(eq_addr);
	*shmem = frame_addr & PAGE_FRAME_L48_MASK;
	all_addr_h4bits |= (frame_addr >> PAGE_FRAME_L48_WIDTH_BITS) <<
		(frame_addr_seq++ * PAGE_FRAME_H4_WIDTH_BITS);
	ptr += PAGE_FRAME_L48_WIDTH_BYTES;

	/* CQ addr: low 48 bits of frame address */
	shmem = (u64 *)ptr;
	frame_addr = PHYS_PFN(cq_addr);
	*shmem = frame_addr & PAGE_FRAME_L48_MASK;
	all_addr_h4bits |= (frame_addr >> PAGE_FRAME_L48_WIDTH_BITS) <<
		(frame_addr_seq++ * PAGE_FRAME_H4_WIDTH_BITS);
	ptr += PAGE_FRAME_L48_WIDTH_BYTES;

	/* RQ addr: low 48 bits of frame address */
	shmem = (u64 *)ptr;
	frame_addr = PHYS_PFN(rq_addr);
	*shmem = frame_addr & PAGE_FRAME_L48_MASK;
	all_addr_h4bits |= (frame_addr >> PAGE_FRAME_L48_WIDTH_BITS) <<
		(frame_addr_seq++ * PAGE_FRAME_H4_WIDTH_BITS);
	ptr += PAGE_FRAME_L48_WIDTH_BYTES;

	/* SQ addr: low 48 bits of frame address */
	shmem = (u64 *)ptr;
	frame_addr = PHYS_PFN(sq_addr);
	*shmem = frame_addr & PAGE_FRAME_L48_MASK;
	all_addr_h4bits |= (frame_addr >> PAGE_FRAME_L48_WIDTH_BITS) <<
		(frame_addr_seq++ * PAGE_FRAME_H4_WIDTH_BITS);
	ptr += PAGE_FRAME_L48_WIDTH_BYTES;

	/* High 4 bits of the four frame addresses */
	*((u16 *)ptr) = all_addr_h4bits;
	ptr += माप(u16);

	/* EQ MSIX vector number */
	*((u16 *)ptr) = (u16)eq_msix_index;
	ptr += माप(u16);

	/* 32-bit protocol header in final dword */
	*((u32 *)ptr) = 0;

	hdr = (जोड़ smc_proto_hdr *)ptr;
	hdr->msg_type = SMC_MSG_TYPE_ESTABLISH_HWC;
	hdr->msg_version = SMC_MSG_TYPE_ESTABLISH_HWC_VERSION;
	hdr->direction = SMC_MSG_सूचीECTION_REQUEST;
	hdr->reset_vf = reset_vf;

	/* Write 256-message buffer to shared memory (final 32-bit ग_लिखो
	 * triggers HW to set possession bit to PF).
	 */
	dword = (u32 *)shm_buf;
	क्रम (i = 0; i < SMC_APERTURE_DWORDS; i++)
		ग_लिखोl(*dword++, sc->base + i * SMC_BASIC_UNIT);

	/* Read shmem response (polling क्रम VF possession) and validate.
	 * For setup, रुकोing क्रम response on shared memory is not strictly
	 * necessary, since रुको occurs later क्रम results to appear in EQE's.
	 */
	err = mana_smc_पढ़ो_response(sc, SMC_MSG_TYPE_ESTABLISH_HWC,
				     SMC_MSG_TYPE_ESTABLISH_HWC_VERSION,
				     reset_vf);
	अगर (err) अणु
		dev_err(sc->dev, "Error when setting up HWC: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mana_smc_tearकरोwn_hwc(काष्ठा shm_channel *sc, bool reset_vf)
अणु
	जोड़ smc_proto_hdr hdr = अणुपूर्ण;
	पूर्णांक err;

	/* Ensure alपढ़ोy has possession of shared memory */
	err = mana_smc_poll_रेजिस्टर(sc->base, false);
	अगर (err) अणु
		dev_err(sc->dev, "Timeout when tearing down HWC\n");
		वापस err;
	पूर्ण

	/* Set up protocol header क्रम HWC destroy message */
	hdr.msg_type = SMC_MSG_TYPE_DESTROY_HWC;
	hdr.msg_version = SMC_MSG_TYPE_DESTROY_HWC_VERSION;
	hdr.direction = SMC_MSG_सूचीECTION_REQUEST;
	hdr.reset_vf = reset_vf;

	/* Write message in high 32 bits of 256-bit shared memory, causing HW
	 * to set possession bit to PF.
	 */
	ग_लिखोl(hdr.as_uपूर्णांक32, sc->base + SMC_LAST_DWORD * SMC_BASIC_UNIT);

	/* Read shmem response (polling क्रम VF possession) and validate.
	 * For tearकरोwn, रुकोing क्रम response is required to ensure hardware
	 * invalidates MST entries beक्रमe software मुक्तs memory.
	 */
	err = mana_smc_पढ़ो_response(sc, SMC_MSG_TYPE_DESTROY_HWC,
				     SMC_MSG_TYPE_DESTROY_HWC_VERSION,
				     reset_vf);
	अगर (err) अणु
		dev_err(sc->dev, "Error when tearing down HWC: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
