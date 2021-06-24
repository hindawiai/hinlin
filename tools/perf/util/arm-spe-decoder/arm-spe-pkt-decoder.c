<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Arm Statistical Profiling Extensions (SPE) support
 * Copyright (c) 2017-2018, Arm Ltd.
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <endian.h>
#समावेश <byteswap.h>
#समावेश <linux/bitops.h>
#समावेश <मानकतर्क.स>

#समावेश "arm-spe-pkt-decoder.h"

#अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा le16_to_cpu bswap_16
#घोषणा le32_to_cpu bswap_32
#घोषणा le64_to_cpu bswap_64
#घोषणा स_नकल_le64(d, s, n) करो अणु \
	स_नकल((d), (s), (n));    \
	*(d) = le64_to_cpu(*(d)); \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा le16_to_cpu
#घोषणा le32_to_cpu
#घोषणा le64_to_cpu
#घोषणा स_नकल_le64 स_नकल
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर arm_spe_packet_name[] = अणु
	[ARM_SPE_PAD]		= "PAD",
	[ARM_SPE_END]		= "END",
	[ARM_SPE_TIMESTAMP]	= "TS",
	[ARM_SPE_ADDRESS]	= "ADDR",
	[ARM_SPE_COUNTER]	= "LAT",
	[ARM_SPE_CONTEXT]	= "CONTEXT",
	[ARM_SPE_OP_TYPE]	= "OP-TYPE",
	[ARM_SPE_EVENTS]	= "EVENTS",
	[ARM_SPE_DATA_SOURCE]	= "DATA-SOURCE",
पूर्ण;

स्थिर अक्षर *arm_spe_pkt_name(क्रमागत arm_spe_pkt_type type)
अणु
	वापस arm_spe_packet_name[type];
पूर्ण

/*
 * Extracts the field "sz" from header bits and converts to bytes:
 *   00 : byte (1)
 *   01 : halfword (2)
 *   10 : word (4)
 *   11 : द्विगुनword (8)
 */
अटल अचिन्हित पूर्णांक arm_spe_payload_len(अचिन्हित अक्षर hdr)
अणु
	वापस 1U << ((hdr & GENMASK_ULL(5, 4)) >> 4);
पूर्ण

अटल पूर्णांक arm_spe_get_payload(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			       अचिन्हित अक्षर ext_hdr,
			       काष्ठा arm_spe_pkt *packet)
अणु
	माप_प्रकार payload_len = arm_spe_payload_len(buf[ext_hdr]);

	अगर (len < 1 + ext_hdr + payload_len)
		वापस ARM_SPE_NEED_MORE_BYTES;

	buf += 1 + ext_hdr;

	चयन (payload_len) अणु
	हाल 1: packet->payload = *(uपूर्णांक8_t *)buf; अवरोध;
	हाल 2: packet->payload = le16_to_cpu(*(uपूर्णांक16_t *)buf); अवरोध;
	हाल 4: packet->payload = le32_to_cpu(*(uपूर्णांक32_t *)buf); अवरोध;
	हाल 8: packet->payload = le64_to_cpu(*(uपूर्णांक64_t *)buf); अवरोध;
	शेष: वापस ARM_SPE_BAD_PACKET;
	पूर्ण

	वापस 1 + ext_hdr + payload_len;
पूर्ण

अटल पूर्णांक arm_spe_get_pad(काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_PAD;
	वापस 1;
पूर्ण

अटल पूर्णांक arm_spe_get_alignment(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
				 काष्ठा arm_spe_pkt *packet)
अणु
	अचिन्हित पूर्णांक alignment = 1 << ((buf[0] & 0xf) + 1);

	अगर (len < alignment)
		वापस ARM_SPE_NEED_MORE_BYTES;

	packet->type = ARM_SPE_PAD;
	वापस alignment - (((uपूर्णांकptr_t)buf) & (alignment - 1));
पूर्ण

अटल पूर्णांक arm_spe_get_end(काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_END;
	वापस 1;
पूर्ण

अटल पूर्णांक arm_spe_get_बारtamp(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
				 काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_TIMESTAMP;
	वापस arm_spe_get_payload(buf, len, 0, packet);
पूर्ण

अटल पूर्णांक arm_spe_get_events(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			      काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_EVENTS;

	/* we use index to identअगरy Events with a less number of
	 * comparisons in arm_spe_pkt_desc(): E.g., the LLC-ACCESS,
	 * LLC-REFILL, and REMOTE-ACCESS events are identअगरied अगर
	 * index > 1.
	 */
	packet->index = arm_spe_payload_len(buf[0]);

	वापस arm_spe_get_payload(buf, len, 0, packet);
पूर्ण

अटल पूर्णांक arm_spe_get_data_source(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
				   काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_DATA_SOURCE;
	वापस arm_spe_get_payload(buf, len, 0, packet);
पूर्ण

अटल पूर्णांक arm_spe_get_context(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			       काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_CONTEXT;
	packet->index = SPE_CTX_PKT_HDR_INDEX(buf[0]);
	वापस arm_spe_get_payload(buf, len, 0, packet);
पूर्ण

अटल पूर्णांक arm_spe_get_op_type(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			       काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_OP_TYPE;
	packet->index = SPE_OP_PKT_HDR_CLASS(buf[0]);
	वापस arm_spe_get_payload(buf, len, 0, packet);
पूर्ण

अटल पूर्णांक arm_spe_get_counter(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			       स्थिर अचिन्हित अक्षर ext_hdr, काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_COUNTER;

	अगर (ext_hdr)
		packet->index = SPE_HDR_EXTENDED_INDEX(buf[0], buf[1]);
	अन्यथा
		packet->index = SPE_HDR_SHORT_INDEX(buf[0]);

	वापस arm_spe_get_payload(buf, len, ext_hdr, packet);
पूर्ण

अटल पूर्णांक arm_spe_get_addr(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    स्थिर अचिन्हित अक्षर ext_hdr, काष्ठा arm_spe_pkt *packet)
अणु
	packet->type = ARM_SPE_ADDRESS;

	अगर (ext_hdr)
		packet->index = SPE_HDR_EXTENDED_INDEX(buf[0], buf[1]);
	अन्यथा
		packet->index = SPE_HDR_SHORT_INDEX(buf[0]);

	वापस arm_spe_get_payload(buf, len, ext_hdr, packet);
पूर्ण

अटल पूर्णांक arm_spe_करो_get_packet(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
				 काष्ठा arm_spe_pkt *packet)
अणु
	अचिन्हित पूर्णांक hdr;
	अचिन्हित अक्षर ext_hdr = 0;

	स_रखो(packet, 0, माप(काष्ठा arm_spe_pkt));

	अगर (!len)
		वापस ARM_SPE_NEED_MORE_BYTES;

	hdr = buf[0];

	अगर (hdr == SPE_HEADER0_PAD)
		वापस arm_spe_get_pad(packet);

	अगर (hdr == SPE_HEADER0_END) /* no बारtamp at end of record */
		वापस arm_spe_get_end(packet);

	अगर (hdr == SPE_HEADER0_TIMESTAMP)
		वापस arm_spe_get_बारtamp(buf, len, packet);

	अगर ((hdr & SPE_HEADER0_MASK1) == SPE_HEADER0_EVENTS)
		वापस arm_spe_get_events(buf, len, packet);

	अगर ((hdr & SPE_HEADER0_MASK1) == SPE_HEADER0_SOURCE)
		वापस arm_spe_get_data_source(buf, len, packet);

	अगर ((hdr & SPE_HEADER0_MASK2) == SPE_HEADER0_CONTEXT)
		वापस arm_spe_get_context(buf, len, packet);

	अगर ((hdr & SPE_HEADER0_MASK2) == SPE_HEADER0_OP_TYPE)
		वापस arm_spe_get_op_type(buf, len, packet);

	अगर ((hdr & SPE_HEADER0_MASK2) == SPE_HEADER0_EXTENDED) अणु
		/* 16-bit extended क्रमmat header */
		अगर (len == 1)
			वापस ARM_SPE_BAD_PACKET;

		ext_hdr = 1;
		hdr = buf[1];
		अगर (hdr == SPE_HEADER1_ALIGNMENT)
			वापस arm_spe_get_alignment(buf, len, packet);
	पूर्ण

	/*
	 * The लघु क्रमmat header's byte 0 or the extended format header's
	 * byte 1 has been asचिन्हित to 'hdr', which uses the same encoding क्रम
	 * address packet and counter packet, so करोn't need to distinguish अगर
	 * it's लघु क्रमmat or extended क्रमmat and handle in once.
	 */
	अगर ((hdr & SPE_HEADER0_MASK3) == SPE_HEADER0_ADDRESS)
		वापस arm_spe_get_addr(buf, len, ext_hdr, packet);

	अगर ((hdr & SPE_HEADER0_MASK3) == SPE_HEADER0_COUNTER)
		वापस arm_spe_get_counter(buf, len, ext_hdr, packet);

	वापस ARM_SPE_BAD_PACKET;
पूर्ण

पूर्णांक arm_spe_get_packet(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
		       काष्ठा arm_spe_pkt *packet)
अणु
	पूर्णांक ret;

	ret = arm_spe_करो_get_packet(buf, len, packet);
	/* put multiple consecutive PADs on the same line, up to
	 * the fixed-width output क्रमmat of 16 bytes per line.
	 */
	अगर (ret > 0 && packet->type == ARM_SPE_PAD) अणु
		जबतक (ret < 16 && len > (माप_प्रकार)ret && !buf[ret])
			ret += 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक arm_spe_pkt_out_string(पूर्णांक *err, अक्षर **buf_p, माप_प्रकार *blen,
				  स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	/* Bail out अगर any error occurred */
	अगर (err && *err)
		वापस *err;

	बहु_शुरू(ap, fmt);
	ret = vsnम_लिखो(*buf_p, *blen, fmt, ap);
	बहु_पूर्ण(ap);

	अगर (ret < 0) अणु
		अगर (err && !*err)
			*err = ret;

	/*
	 * A वापस value of *blen or more means that the output was
	 * truncated and the buffer is overrun.
	 */
	पूर्ण अन्यथा अगर ((माप_प्रकार)ret >= *blen) अणु
		(*buf_p)[*blen - 1] = '\0';

		/*
		 * Set *err to 'ret' to aव्योम overflow अगर tries to
		 * fill this buffer sequentially.
		 */
		अगर (err && !*err)
			*err = ret;
	पूर्ण अन्यथा अणु
		*buf_p += ret;
		*blen -= ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक arm_spe_pkt_desc_event(स्थिर काष्ठा arm_spe_pkt *packet,
				  अक्षर *buf, माप_प्रकार buf_len)
अणु
	u64 payload = packet->payload;
	पूर्णांक err = 0;

	arm_spe_pkt_out_string(&err, &buf, &buf_len, "EV");

	अगर (payload & BIT(EV_EXCEPTION_GEN))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " EXCEPTION-GEN");
	अगर (payload & BIT(EV_RETIRED))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " RETIRED");
	अगर (payload & BIT(EV_L1D_ACCESS))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " L1D-ACCESS");
	अगर (payload & BIT(EV_L1D_REFILL))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " L1D-REFILL");
	अगर (payload & BIT(EV_TLB_ACCESS))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " TLB-ACCESS");
	अगर (payload & BIT(EV_TLB_WALK))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " TLB-REFILL");
	अगर (payload & BIT(EV_NOT_TAKEN))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " NOT-TAKEN");
	अगर (payload & BIT(EV_MISPRED))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " MISPRED");
	अगर (payload & BIT(EV_LLC_ACCESS))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " LLC-ACCESS");
	अगर (payload & BIT(EV_LLC_MISS))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " LLC-REFILL");
	अगर (payload & BIT(EV_REMOTE_ACCESS))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " REMOTE-ACCESS");
	अगर (payload & BIT(EV_ALIGNMENT))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " ALIGNMENT");
	अगर (payload & BIT(EV_PARTIAL_PREDICATE))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " SVE-PARTIAL-PRED");
	अगर (payload & BIT(EV_EMPTY_PREDICATE))
		arm_spe_pkt_out_string(&err, &buf, &buf_len, " SVE-EMPTY-PRED");

	वापस err;
पूर्ण

अटल पूर्णांक arm_spe_pkt_desc_op_type(स्थिर काष्ठा arm_spe_pkt *packet,
				    अक्षर *buf, माप_प्रकार buf_len)
अणु
	u64 payload = packet->payload;
	पूर्णांक err = 0;

	चयन (packet->index) अणु
	हाल SPE_OP_PKT_HDR_CLASS_OTHER:
		अगर (SPE_OP_PKT_IS_OTHER_SVE_OP(payload)) अणु
			arm_spe_pkt_out_string(&err, &buf, &buf_len, "SVE-OTHER");

			/* SVE effective vector length */
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " EVLEN %d",
					       SPE_OP_PKG_SVE_EVL(payload));

			अगर (payload & SPE_OP_PKT_SVE_FP)
				arm_spe_pkt_out_string(&err, &buf, &buf_len, " FP");
			अगर (payload & SPE_OP_PKT_SVE_PRED)
				arm_spe_pkt_out_string(&err, &buf, &buf_len, " PRED");
		पूर्ण अन्यथा अणु
			arm_spe_pkt_out_string(&err, &buf, &buf_len, "OTHER");
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " %s",
					       payload & SPE_OP_PKT_COND ?
					       "COND-SELECT" : "INSN-OTHER");
		पूर्ण
		अवरोध;
	हाल SPE_OP_PKT_HDR_CLASS_LD_ST_ATOMIC:
		arm_spe_pkt_out_string(&err, &buf, &buf_len,
				       payload & 0x1 ? "ST" : "LD");

		अगर (SPE_OP_PKT_IS_LDST_ATOMIC(payload)) अणु
			अगर (payload & SPE_OP_PKT_AT)
				arm_spe_pkt_out_string(&err, &buf, &buf_len, " AT");
			अगर (payload & SPE_OP_PKT_EXCL)
				arm_spe_pkt_out_string(&err, &buf, &buf_len, " EXCL");
			अगर (payload & SPE_OP_PKT_AR)
				arm_spe_pkt_out_string(&err, &buf, &buf_len, " AR");
		पूर्ण

		चयन (SPE_OP_PKT_LDST_SUBCLASS_GET(payload)) अणु
		हाल SPE_OP_PKT_LDST_SUBCLASS_SIMD_FP:
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " SIMD-FP");
			अवरोध;
		हाल SPE_OP_PKT_LDST_SUBCLASS_GP_REG:
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " GP-REG");
			अवरोध;
		हाल SPE_OP_PKT_LDST_SUBCLASS_UNSPEC_REG:
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " UNSPEC-REG");
			अवरोध;
		हाल SPE_OP_PKT_LDST_SUBCLASS_NV_SYSREG:
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " NV-SYSREG");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (SPE_OP_PKT_IS_LDST_SVE(payload)) अणु
			/* SVE effective vector length */
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " EVLEN %d",
					       SPE_OP_PKG_SVE_EVL(payload));

			अगर (payload & SPE_OP_PKT_SVE_PRED)
				arm_spe_pkt_out_string(&err, &buf, &buf_len, " PRED");
			अगर (payload & SPE_OP_PKT_SVE_SG)
				arm_spe_pkt_out_string(&err, &buf, &buf_len, " SG");
		पूर्ण
		अवरोध;
	हाल SPE_OP_PKT_HDR_CLASS_BR_ERET:
		arm_spe_pkt_out_string(&err, &buf, &buf_len, "B");

		अगर (payload & SPE_OP_PKT_COND)
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " COND");

		अगर (SPE_OP_PKT_IS_INसूचीECT_BRANCH(payload))
			arm_spe_pkt_out_string(&err, &buf, &buf_len, " IND");

		अवरोध;
	शेष:
		/* Unknown index */
		err = -1;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक arm_spe_pkt_desc_addr(स्थिर काष्ठा arm_spe_pkt *packet,
				 अक्षर *buf, माप_प्रकार buf_len)
अणु
	पूर्णांक ns, el, idx = packet->index;
	पूर्णांक ch, pat;
	u64 payload = packet->payload;
	पूर्णांक err = 0;

	चयन (idx) अणु
	हाल SPE_ADDR_PKT_HDR_INDEX_INS:
	हाल SPE_ADDR_PKT_HDR_INDEX_BRANCH:
		ns = !!SPE_ADDR_PKT_GET_NS(payload);
		el = SPE_ADDR_PKT_GET_EL(payload);
		payload = SPE_ADDR_PKT_ADDR_GET_BYTES_0_6(payload);
		arm_spe_pkt_out_string(&err, &buf, &buf_len,
				"%s 0x%llx el%d ns=%d",
				(idx == 1) ? "TGT" : "PC", payload, el, ns);
		अवरोध;
	हाल SPE_ADDR_PKT_HDR_INDEX_DATA_VIRT:
		arm_spe_pkt_out_string(&err, &buf, &buf_len,
				       "VA 0x%llx", payload);
		अवरोध;
	हाल SPE_ADDR_PKT_HDR_INDEX_DATA_PHYS:
		ns = !!SPE_ADDR_PKT_GET_NS(payload);
		ch = !!SPE_ADDR_PKT_GET_CH(payload);
		pat = SPE_ADDR_PKT_GET_PAT(payload);
		payload = SPE_ADDR_PKT_ADDR_GET_BYTES_0_6(payload);
		arm_spe_pkt_out_string(&err, &buf, &buf_len,
				       "PA 0x%llx ns=%d ch=%d pat=%x",
				       payload, ns, ch, pat);
		अवरोध;
	शेष:
		/* Unknown index */
		err = -1;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक arm_spe_pkt_desc_counter(स्थिर काष्ठा arm_spe_pkt *packet,
				    अक्षर *buf, माप_प्रकार buf_len)
अणु
	u64 payload = packet->payload;
	स्थिर अक्षर *name = arm_spe_pkt_name(packet->type);
	पूर्णांक err = 0;

	arm_spe_pkt_out_string(&err, &buf, &buf_len, "%s %d ", name,
			       (अचिन्हित लघु)payload);

	चयन (packet->index) अणु
	हाल SPE_CNT_PKT_HDR_INDEX_TOTAL_LAT:
		arm_spe_pkt_out_string(&err, &buf, &buf_len, "TOT");
		अवरोध;
	हाल SPE_CNT_PKT_HDR_INDEX_ISSUE_LAT:
		arm_spe_pkt_out_string(&err, &buf, &buf_len, "ISSUE");
		अवरोध;
	हाल SPE_CNT_PKT_HDR_INDEX_TRANS_LAT:
		arm_spe_pkt_out_string(&err, &buf, &buf_len, "XLAT");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक arm_spe_pkt_desc(स्थिर काष्ठा arm_spe_pkt *packet, अक्षर *buf,
		     माप_प्रकार buf_len)
अणु
	पूर्णांक idx = packet->index;
	अचिन्हित दीर्घ दीर्घ payload = packet->payload;
	स्थिर अक्षर *name = arm_spe_pkt_name(packet->type);
	अक्षर *buf_orig = buf;
	माप_प्रकार blen = buf_len;
	पूर्णांक err = 0;

	चयन (packet->type) अणु
	हाल ARM_SPE_BAD:
	हाल ARM_SPE_PAD:
	हाल ARM_SPE_END:
		arm_spe_pkt_out_string(&err, &buf, &blen, "%s", name);
		अवरोध;
	हाल ARM_SPE_EVENTS:
		err = arm_spe_pkt_desc_event(packet, buf, buf_len);
		अवरोध;
	हाल ARM_SPE_OP_TYPE:
		err = arm_spe_pkt_desc_op_type(packet, buf, buf_len);
		अवरोध;
	हाल ARM_SPE_DATA_SOURCE:
	हाल ARM_SPE_TIMESTAMP:
		arm_spe_pkt_out_string(&err, &buf, &blen, "%s %lld", name, payload);
		अवरोध;
	हाल ARM_SPE_ADDRESS:
		err = arm_spe_pkt_desc_addr(packet, buf, buf_len);
		अवरोध;
	हाल ARM_SPE_CONTEXT:
		arm_spe_pkt_out_string(&err, &buf, &blen, "%s 0x%lx el%d",
				       name, (अचिन्हित दीर्घ)payload, idx + 1);
		अवरोध;
	हाल ARM_SPE_COUNTER:
		err = arm_spe_pkt_desc_counter(packet, buf, buf_len);
		अवरोध;
	शेष:
		/* Unknown packet type */
		err = -1;
		अवरोध;
	पूर्ण

	/* Output raw data अगर detect any error */
	अगर (err) अणु
		err = 0;
		arm_spe_pkt_out_string(&err, &buf_orig, &buf_len, "%s 0x%llx (%d)",
				       name, payload, packet->index);
	पूर्ण

	वापस err;
पूर्ण
