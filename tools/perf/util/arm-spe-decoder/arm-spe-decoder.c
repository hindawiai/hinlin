<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arm_spe_decoder.c: ARM SPE support
 */

#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/zभाग.स>

#समावेश "../auxtrace.h"
#समावेश "../debug.h"
#समावेश "../util.h"

#समावेश "arm-spe-decoder.h"

अटल u64 arm_spe_calc_ip(पूर्णांक index, u64 payload)
अणु
	u64 ns, el, val;

	/* Inकाष्ठाion भव address or Branch target address */
	अगर (index == SPE_ADDR_PKT_HDR_INDEX_INS ||
	    index == SPE_ADDR_PKT_HDR_INDEX_BRANCH) अणु
		ns = SPE_ADDR_PKT_GET_NS(payload);
		el = SPE_ADDR_PKT_GET_EL(payload);

		/* Clean highest byte */
		payload = SPE_ADDR_PKT_ADDR_GET_BYTES_0_6(payload);

		/* Fill highest byte क्रम EL1 or EL2 (VHE) mode */
		अगर (ns && (el == SPE_ADDR_PKT_EL1 || el == SPE_ADDR_PKT_EL2))
			payload |= 0xffULL << SPE_ADDR_PKT_ADDR_BYTE7_SHIFT;

	/* Data access भव address */
	पूर्ण अन्यथा अगर (index == SPE_ADDR_PKT_HDR_INDEX_DATA_VIRT) अणु

		/* Clean tags */
		payload = SPE_ADDR_PKT_ADDR_GET_BYTES_0_6(payload);

		/*
		 * Armv8 ARM (ARM DDI 0487F.c), chapter "D10.2.1 Address packet"
		 * defines the data भव address payload क्रमmat, the top byte
		 * (bits [63:56]) is asचिन्हित as top-byte tag; so we only can
		 * retrieve address value from bits [55:0].
		 *
		 * According to Documentation/arm64/memory.rst, अगर detects the
		 * specअगरic pattern in bits [55:52] of payload which falls in
		 * the kernel space, should fixup the top byte and this allows
		 * perf tool to parse DSO symbol क्रम data address correctly.
		 *
		 * For this reason, अगर detects the bits [55:52] is 0xf, will
		 * fill 0xff पूर्णांकo the top byte.
		 */
		val = SPE_ADDR_PKT_ADDR_GET_BYTE_6(payload);
		अगर ((val & 0xf0ULL) == 0xf0ULL)
			payload |= 0xffULL << SPE_ADDR_PKT_ADDR_BYTE7_SHIFT;

	/* Data access physical address */
	पूर्ण अन्यथा अगर (index == SPE_ADDR_PKT_HDR_INDEX_DATA_PHYS) अणु
		/* Clean highest byte */
		payload = SPE_ADDR_PKT_ADDR_GET_BYTES_0_6(payload);
	पूर्ण अन्यथा अणु
		pr_err("unsupported address packet index: 0x%x\n", index);
	पूर्ण

	वापस payload;
पूर्ण

काष्ठा arm_spe_decoder *arm_spe_decoder_new(काष्ठा arm_spe_params *params)
अणु
	काष्ठा arm_spe_decoder *decoder;

	अगर (!params->get_trace)
		वापस शून्य;

	decoder = zalloc(माप(काष्ठा arm_spe_decoder));
	अगर (!decoder)
		वापस शून्य;

	decoder->get_trace = params->get_trace;
	decoder->data = params->data;

	वापस decoder;
पूर्ण

व्योम arm_spe_decoder_मुक्त(काष्ठा arm_spe_decoder *decoder)
अणु
	मुक्त(decoder);
पूर्ण

अटल पूर्णांक arm_spe_get_data(काष्ठा arm_spe_decoder *decoder)
अणु
	काष्ठा arm_spe_buffer buffer = अणु .buf = 0, पूर्ण;
	पूर्णांक ret;

	pr_debug("Getting more data\n");
	ret = decoder->get_trace(&buffer, decoder->data);
	अगर (ret < 0)
		वापस ret;

	decoder->buf = buffer.buf;
	decoder->len = buffer.len;

	अगर (!decoder->len)
		pr_debug("No more data\n");

	वापस decoder->len;
पूर्ण

अटल पूर्णांक arm_spe_get_next_packet(काष्ठा arm_spe_decoder *decoder)
अणु
	पूर्णांक ret;

	करो अणु
		अगर (!decoder->len) अणु
			ret = arm_spe_get_data(decoder);

			/* Failed to पढ़ो out trace data */
			अगर (ret <= 0)
				वापस ret;
		पूर्ण

		ret = arm_spe_get_packet(decoder->buf, decoder->len,
					 &decoder->packet);
		अगर (ret <= 0) अणु
			/* Move क्रमward क्रम 1 byte */
			decoder->buf += 1;
			decoder->len -= 1;
			वापस -EBADMSG;
		पूर्ण

		decoder->buf += ret;
		decoder->len -= ret;
	पूर्ण जबतक (decoder->packet.type == ARM_SPE_PAD);

	वापस 1;
पूर्ण

अटल पूर्णांक arm_spe_पढ़ो_record(काष्ठा arm_spe_decoder *decoder)
अणु
	पूर्णांक err;
	पूर्णांक idx;
	u64 payload, ip;

	स_रखो(&decoder->record, 0x0, माप(decoder->record));

	जबतक (1) अणु
		err = arm_spe_get_next_packet(decoder);
		अगर (err <= 0)
			वापस err;

		idx = decoder->packet.index;
		payload = decoder->packet.payload;

		चयन (decoder->packet.type) अणु
		हाल ARM_SPE_TIMESTAMP:
			decoder->record.बारtamp = payload;
			वापस 1;
		हाल ARM_SPE_END:
			वापस 1;
		हाल ARM_SPE_ADDRESS:
			ip = arm_spe_calc_ip(idx, payload);
			अगर (idx == SPE_ADDR_PKT_HDR_INDEX_INS)
				decoder->record.from_ip = ip;
			अन्यथा अगर (idx == SPE_ADDR_PKT_HDR_INDEX_BRANCH)
				decoder->record.to_ip = ip;
			अन्यथा अगर (idx == SPE_ADDR_PKT_HDR_INDEX_DATA_VIRT)
				decoder->record.virt_addr = ip;
			अन्यथा अगर (idx == SPE_ADDR_PKT_HDR_INDEX_DATA_PHYS)
				decoder->record.phys_addr = ip;
			अवरोध;
		हाल ARM_SPE_COUNTER:
			अवरोध;
		हाल ARM_SPE_CONTEXT:
			अवरोध;
		हाल ARM_SPE_OP_TYPE:
			अगर (idx == SPE_OP_PKT_HDR_CLASS_LD_ST_ATOMIC) अणु
				अगर (payload & 0x1)
					decoder->record.op = ARM_SPE_ST;
				अन्यथा
					decoder->record.op = ARM_SPE_LD;
			पूर्ण
			अवरोध;
		हाल ARM_SPE_EVENTS:
			अगर (payload & BIT(EV_L1D_REFILL))
				decoder->record.type |= ARM_SPE_L1D_MISS;

			अगर (payload & BIT(EV_L1D_ACCESS))
				decoder->record.type |= ARM_SPE_L1D_ACCESS;

			अगर (payload & BIT(EV_TLB_WALK))
				decoder->record.type |= ARM_SPE_TLB_MISS;

			अगर (payload & BIT(EV_TLB_ACCESS))
				decoder->record.type |= ARM_SPE_TLB_ACCESS;

			अगर (payload & BIT(EV_LLC_MISS))
				decoder->record.type |= ARM_SPE_LLC_MISS;

			अगर (payload & BIT(EV_LLC_ACCESS))
				decoder->record.type |= ARM_SPE_LLC_ACCESS;

			अगर (payload & BIT(EV_REMOTE_ACCESS))
				decoder->record.type |= ARM_SPE_REMOTE_ACCESS;

			अगर (payload & BIT(EV_MISPRED))
				decoder->record.type |= ARM_SPE_BRANCH_MISS;

			अवरोध;
		हाल ARM_SPE_DATA_SOURCE:
			अवरोध;
		हाल ARM_SPE_BAD:
			अवरोध;
		हाल ARM_SPE_PAD:
			अवरोध;
		शेष:
			pr_err("Get packet error!\n");
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक arm_spe_decode(काष्ठा arm_spe_decoder *decoder)
अणु
	वापस arm_spe_पढ़ो_record(decoder);
पूर्ण
