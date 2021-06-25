<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_pt_pkt_decoder.c: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <endian.h>
#समावेश <byteswap.h>
#समावेश <linux/compiler.h>

#समावेश "intel-pt-pkt-decoder.h"

#घोषणा BIT(n)		(1 << (n))

#घोषणा BIT63		((uपूर्णांक64_t)1 << 63)

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

अटल स्थिर अक्षर * स्थिर packet_name[] = अणु
	[INTEL_PT_BAD]		= "Bad Packet!",
	[INTEL_PT_PAD]		= "PAD",
	[INTEL_PT_TNT]		= "TNT",
	[INTEL_PT_TIP_PGD]	= "TIP.PGD",
	[INTEL_PT_TIP_PGE]	= "TIP.PGE",
	[INTEL_PT_TSC]		= "TSC",
	[INTEL_PT_TMA]		= "TMA",
	[INTEL_PT_MODE_EXEC]	= "MODE.Exec",
	[INTEL_PT_MODE_TSX]	= "MODE.TSX",
	[INTEL_PT_MTC]		= "MTC",
	[INTEL_PT_TIP]		= "TIP",
	[INTEL_PT_FUP]		= "FUP",
	[INTEL_PT_CYC]		= "CYC",
	[INTEL_PT_VMCS]		= "VMCS",
	[INTEL_PT_PSB]		= "PSB",
	[INTEL_PT_PSBEND]	= "PSBEND",
	[INTEL_PT_CBR]		= "CBR",
	[INTEL_PT_TRACESTOP]	= "TraceSTOP",
	[INTEL_PT_PIP]		= "PIP",
	[INTEL_PT_OVF]		= "OVF",
	[INTEL_PT_MNT]		= "MNT",
	[INTEL_PT_PTWRITE]	= "PTWRITE",
	[INTEL_PT_PTWRITE_IP]	= "PTWRITE",
	[INTEL_PT_EXSTOP]	= "EXSTOP",
	[INTEL_PT_EXSTOP_IP]	= "EXSTOP",
	[INTEL_PT_MWAIT]	= "MWAIT",
	[INTEL_PT_PWRE]		= "PWRE",
	[INTEL_PT_PWRX]		= "PWRX",
	[INTEL_PT_BBP]		= "BBP",
	[INTEL_PT_BIP]		= "BIP",
	[INTEL_PT_BEP]		= "BEP",
	[INTEL_PT_BEP_IP]	= "BEP",
पूर्ण;

स्थिर अक्षर *पूर्णांकel_pt_pkt_name(क्रमागत पूर्णांकel_pt_pkt_type type)
अणु
	वापस packet_name[type];
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_दीर्घ_tnt(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
				 काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	uपूर्णांक64_t payload;
	पूर्णांक count;

	अगर (len < 8)
		वापस INTEL_PT_NEED_MORE_BYTES;

	payload = le64_to_cpu(*(uपूर्णांक64_t *)buf);

	क्रम (count = 47; count; count--) अणु
		अगर (payload & BIT63)
			अवरोध;
		payload <<= 1;
	पूर्ण

	packet->type = INTEL_PT_TNT;
	packet->count = count;
	packet->payload = payload << 1;
	वापस 8;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_pip(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	uपूर्णांक64_t payload = 0;

	अगर (len < 8)
		वापस INTEL_PT_NEED_MORE_BYTES;

	packet->type = INTEL_PT_PIP;
	स_नकल_le64(&payload, buf + 2, 6);
	packet->payload = payload;

	वापस 8;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_tracestop(काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	packet->type = INTEL_PT_TRACESTOP;
	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_cbr(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 4)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_CBR;
	packet->payload = le16_to_cpu(*(uपूर्णांक16_t *)(buf + 2));
	वापस 4;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_vmcs(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			     काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अचिन्हित पूर्णांक count = (52 - 5) >> 3;

	अगर (count < 1 || count > 7)
		वापस INTEL_PT_BAD_PACKET;

	अगर (len < count + 2)
		वापस INTEL_PT_NEED_MORE_BYTES;

	packet->type = INTEL_PT_VMCS;
	packet->count = count;
	स_नकल_le64(&packet->payload, buf + 2, count);

	वापस count + 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_ovf(काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	packet->type = INTEL_PT_OVF;
	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_psb(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	पूर्णांक i;

	अगर (len < 16)
		वापस INTEL_PT_NEED_MORE_BYTES;

	क्रम (i = 2; i < 16; i += 2) अणु
		अगर (buf[i] != 2 || buf[i + 1] != 0x82)
			वापस INTEL_PT_BAD_PACKET;
	पूर्ण

	packet->type = INTEL_PT_PSB;
	वापस 16;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_psbend(काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	packet->type = INTEL_PT_PSBEND;
	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_पंचांगa(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 7)
		वापस INTEL_PT_NEED_MORE_BYTES;

	packet->type = INTEL_PT_TMA;
	packet->payload = buf[2] | (buf[3] << 8);
	packet->count = buf[5] | ((buf[6] & BIT(0)) << 8);
	वापस 7;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_pad(काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	packet->type = INTEL_PT_PAD;
	वापस 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_mnt(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 11)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_MNT;
	स_नकल_le64(&packet->payload, buf + 3, 8);
	वापस 11
;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_3byte(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			      काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 3)
		वापस INTEL_PT_NEED_MORE_BYTES;

	चयन (buf[2]) अणु
	हाल 0x88: /* MNT */
		वापस पूर्णांकel_pt_get_mnt(buf, len, packet);
	शेष:
		वापस INTEL_PT_BAD_PACKET;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_ptग_लिखो(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
				काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	packet->count = (buf[1] >> 5) & 0x3;
	packet->type = buf[1] & BIT(7) ? INTEL_PT_PTWRITE_IP :
					 INTEL_PT_PTWRITE;

	चयन (packet->count) अणु
	हाल 0:
		अगर (len < 6)
			वापस INTEL_PT_NEED_MORE_BYTES;
		packet->payload = le32_to_cpu(*(uपूर्णांक32_t *)(buf + 2));
		वापस 6;
	हाल 1:
		अगर (len < 10)
			वापस INTEL_PT_NEED_MORE_BYTES;
		packet->payload = le64_to_cpu(*(uपूर्णांक64_t *)(buf + 2));
		वापस 10;
	शेष:
		वापस INTEL_PT_BAD_PACKET;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_exstop(काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	packet->type = INTEL_PT_EXSTOP;
	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_exstop_ip(काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	packet->type = INTEL_PT_EXSTOP_IP;
	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_mरुको(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			      काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 10)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_MWAIT;
	packet->payload = le64_to_cpu(*(uपूर्णांक64_t *)(buf + 2));
	वापस 10;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_pwre(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			     काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 4)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_PWRE;
	स_नकल_le64(&packet->payload, buf + 2, 2);
	वापस 4;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_pwrx(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			     काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 7)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_PWRX;
	स_नकल_le64(&packet->payload, buf + 2, 5);
	वापस 7;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_bbp(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 3)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_BBP;
	packet->count = buf[2] >> 7;
	packet->payload = buf[2] & 0x1f;
	वापस 3;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_bip_4(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			      काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 5)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_BIP;
	packet->count = buf[0] >> 3;
	स_नकल_le64(&packet->payload, buf + 1, 4);
	वापस 5;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_bip_8(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			      काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 9)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_BIP;
	packet->count = buf[0] >> 3;
	स_नकल_le64(&packet->payload, buf + 1, 8);
	वापस 9;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_bep(माप_प्रकार len, काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 2)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_BEP;
	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_bep_ip(माप_प्रकार len, काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 2)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_BEP_IP;
	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_ext(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 2)
		वापस INTEL_PT_NEED_MORE_BYTES;

	अगर ((buf[1] & 0x1f) == 0x12)
		वापस पूर्णांकel_pt_get_ptग_लिखो(buf, len, packet);

	चयन (buf[1]) अणु
	हाल 0xa3: /* Long TNT */
		वापस पूर्णांकel_pt_get_दीर्घ_tnt(buf, len, packet);
	हाल 0x43: /* PIP */
		वापस पूर्णांकel_pt_get_pip(buf, len, packet);
	हाल 0x83: /* TraceStop */
		वापस पूर्णांकel_pt_get_tracestop(packet);
	हाल 0x03: /* CBR */
		वापस पूर्णांकel_pt_get_cbr(buf, len, packet);
	हाल 0xc8: /* VMCS */
		वापस पूर्णांकel_pt_get_vmcs(buf, len, packet);
	हाल 0xf3: /* OVF */
		वापस पूर्णांकel_pt_get_ovf(packet);
	हाल 0x82: /* PSB */
		वापस पूर्णांकel_pt_get_psb(buf, len, packet);
	हाल 0x23: /* PSBEND */
		वापस पूर्णांकel_pt_get_psbend(packet);
	हाल 0x73: /* TMA */
		वापस पूर्णांकel_pt_get_पंचांगa(buf, len, packet);
	हाल 0xC3: /* 3-byte header */
		वापस पूर्णांकel_pt_get_3byte(buf, len, packet);
	हाल 0x62: /* EXSTOP no IP */
		वापस पूर्णांकel_pt_get_exstop(packet);
	हाल 0xE2: /* EXSTOP with IP */
		वापस पूर्णांकel_pt_get_exstop_ip(packet);
	हाल 0xC2: /* MWAIT */
		वापस पूर्णांकel_pt_get_mरुको(buf, len, packet);
	हाल 0x22: /* PWRE */
		वापस पूर्णांकel_pt_get_pwre(buf, len, packet);
	हाल 0xA2: /* PWRX */
		वापस पूर्णांकel_pt_get_pwrx(buf, len, packet);
	हाल 0x63: /* BBP */
		वापस पूर्णांकel_pt_get_bbp(buf, len, packet);
	हाल 0x33: /* BEP no IP */
		वापस पूर्णांकel_pt_get_bep(len, packet);
	हाल 0xb3: /* BEP with IP */
		वापस पूर्णांकel_pt_get_bep_ip(len, packet);
	शेष:
		वापस INTEL_PT_BAD_PACKET;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_लघु_tnt(अचिन्हित पूर्णांक byte,
				  काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	पूर्णांक count;

	क्रम (count = 6; count; count--) अणु
		अगर (byte & BIT(7))
			अवरोध;
		byte <<= 1;
	पूर्ण

	packet->type = INTEL_PT_TNT;
	packet->count = count;
	packet->payload = (uपूर्णांक64_t)byte << 57;

	वापस 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_cyc(अचिन्हित पूर्णांक byte, स्थिर अचिन्हित अक्षर *buf,
			    माप_प्रकार len, काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अचिन्हित पूर्णांक offs = 1, shअगरt;
	uपूर्णांक64_t payload = byte >> 3;

	byte >>= 2;
	len -= 1;
	क्रम (shअगरt = 5; byte & 1; shअगरt += 7) अणु
		अगर (offs > 9)
			वापस INTEL_PT_BAD_PACKET;
		अगर (len < offs)
			वापस INTEL_PT_NEED_MORE_BYTES;
		byte = buf[offs++];
		payload |= ((uपूर्णांक64_t)byte >> 1) << shअगरt;
	पूर्ण

	packet->type = INTEL_PT_CYC;
	packet->payload = payload;
	वापस offs;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_ip(क्रमागत पूर्णांकel_pt_pkt_type type, अचिन्हित पूर्णांक byte,
			   स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			   काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	पूर्णांक ip_len;

	packet->count = byte >> 5;

	चयन (packet->count) अणु
	हाल 0:
		ip_len = 0;
		अवरोध;
	हाल 1:
		अगर (len < 3)
			वापस INTEL_PT_NEED_MORE_BYTES;
		ip_len = 2;
		packet->payload = le16_to_cpu(*(uपूर्णांक16_t *)(buf + 1));
		अवरोध;
	हाल 2:
		अगर (len < 5)
			वापस INTEL_PT_NEED_MORE_BYTES;
		ip_len = 4;
		packet->payload = le32_to_cpu(*(uपूर्णांक32_t *)(buf + 1));
		अवरोध;
	हाल 3:
	हाल 4:
		अगर (len < 7)
			वापस INTEL_PT_NEED_MORE_BYTES;
		ip_len = 6;
		स_नकल_le64(&packet->payload, buf + 1, 6);
		अवरोध;
	हाल 6:
		अगर (len < 9)
			वापस INTEL_PT_NEED_MORE_BYTES;
		ip_len = 8;
		packet->payload = le64_to_cpu(*(uपूर्णांक64_t *)(buf + 1));
		अवरोध;
	शेष:
		वापस INTEL_PT_BAD_PACKET;
	पूर्ण

	packet->type = type;

	वापस ip_len + 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_mode(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			     काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 2)
		वापस INTEL_PT_NEED_MORE_BYTES;

	चयन (buf[1] >> 5) अणु
	हाल 0:
		packet->type = INTEL_PT_MODE_EXEC;
		चयन (buf[1] & 3) अणु
		हाल 0:
			packet->payload = 16;
			अवरोध;
		हाल 1:
			packet->payload = 64;
			अवरोध;
		हाल 2:
			packet->payload = 32;
			अवरोध;
		शेष:
			वापस INTEL_PT_BAD_PACKET;
		पूर्ण
		अवरोध;
	हाल 1:
		packet->type = INTEL_PT_MODE_TSX;
		अगर ((buf[1] & 3) == 3)
			वापस INTEL_PT_BAD_PACKET;
		packet->payload = buf[1] & 3;
		अवरोध;
	शेष:
		वापस INTEL_PT_BAD_PACKET;
	पूर्ण

	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_tsc(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 8)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_TSC;
	स_नकल_le64(&packet->payload, buf + 1, 7);
	वापस 8;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_mtc(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			    काष्ठा पूर्णांकel_pt_pkt *packet)
अणु
	अगर (len < 2)
		वापस INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_MTC;
	packet->payload = buf[1];
	वापस 2;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_करो_get_packet(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
				  काष्ठा पूर्णांकel_pt_pkt *packet,
				  क्रमागत पूर्णांकel_pt_pkt_ctx ctx)
अणु
	अचिन्हित पूर्णांक byte;

	स_रखो(packet, 0, माप(काष्ठा पूर्णांकel_pt_pkt));

	अगर (!len)
		वापस INTEL_PT_NEED_MORE_BYTES;

	byte = buf[0];

	चयन (ctx) अणु
	हाल INTEL_PT_NO_CTX:
		अवरोध;
	हाल INTEL_PT_BLK_4_CTX:
		अगर ((byte & 0x7) == 4)
			वापस पूर्णांकel_pt_get_bip_4(buf, len, packet);
		अवरोध;
	हाल INTEL_PT_BLK_8_CTX:
		अगर ((byte & 0x7) == 4)
			वापस पूर्णांकel_pt_get_bip_8(buf, len, packet);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!(byte & BIT(0))) अणु
		अगर (byte == 0)
			वापस पूर्णांकel_pt_get_pad(packet);
		अगर (byte == 2)
			वापस पूर्णांकel_pt_get_ext(buf, len, packet);
		वापस पूर्णांकel_pt_get_लघु_tnt(byte, packet);
	पूर्ण

	अगर ((byte & 2))
		वापस पूर्णांकel_pt_get_cyc(byte, buf, len, packet);

	चयन (byte & 0x1f) अणु
	हाल 0x0D:
		वापस पूर्णांकel_pt_get_ip(INTEL_PT_TIP, byte, buf, len, packet);
	हाल 0x11:
		वापस पूर्णांकel_pt_get_ip(INTEL_PT_TIP_PGE, byte, buf, len,
				       packet);
	हाल 0x01:
		वापस पूर्णांकel_pt_get_ip(INTEL_PT_TIP_PGD, byte, buf, len,
				       packet);
	हाल 0x1D:
		वापस पूर्णांकel_pt_get_ip(INTEL_PT_FUP, byte, buf, len, packet);
	हाल 0x19:
		चयन (byte) अणु
		हाल 0x99:
			वापस पूर्णांकel_pt_get_mode(buf, len, packet);
		हाल 0x19:
			वापस पूर्णांकel_pt_get_tsc(buf, len, packet);
		हाल 0x59:
			वापस पूर्णांकel_pt_get_mtc(buf, len, packet);
		शेष:
			वापस INTEL_PT_BAD_PACKET;
		पूर्ण
	शेष:
		वापस INTEL_PT_BAD_PACKET;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_pt_upd_pkt_ctx(स्थिर काष्ठा पूर्णांकel_pt_pkt *packet,
			  क्रमागत पूर्णांकel_pt_pkt_ctx *ctx)
अणु
	चयन (packet->type) अणु
	हाल INTEL_PT_BAD:
	हाल INTEL_PT_PAD:
	हाल INTEL_PT_TSC:
	हाल INTEL_PT_TMA:
	हाल INTEL_PT_MTC:
	हाल INTEL_PT_FUP:
	हाल INTEL_PT_CYC:
	हाल INTEL_PT_CBR:
	हाल INTEL_PT_MNT:
	हाल INTEL_PT_EXSTOP:
	हाल INTEL_PT_EXSTOP_IP:
	हाल INTEL_PT_PWRE:
	हाल INTEL_PT_PWRX:
	हाल INTEL_PT_BIP:
		अवरोध;
	हाल INTEL_PT_TNT:
	हाल INTEL_PT_TIP:
	हाल INTEL_PT_TIP_PGD:
	हाल INTEL_PT_TIP_PGE:
	हाल INTEL_PT_MODE_EXEC:
	हाल INTEL_PT_MODE_TSX:
	हाल INTEL_PT_PIP:
	हाल INTEL_PT_OVF:
	हाल INTEL_PT_VMCS:
	हाल INTEL_PT_TRACESTOP:
	हाल INTEL_PT_PSB:
	हाल INTEL_PT_PSBEND:
	हाल INTEL_PT_PTWRITE:
	हाल INTEL_PT_PTWRITE_IP:
	हाल INTEL_PT_MWAIT:
	हाल INTEL_PT_BEP:
	हाल INTEL_PT_BEP_IP:
		*ctx = INTEL_PT_NO_CTX;
		अवरोध;
	हाल INTEL_PT_BBP:
		अगर (packet->count)
			*ctx = INTEL_PT_BLK_4_CTX;
		अन्यथा
			*ctx = INTEL_PT_BLK_8_CTX;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_pt_get_packet(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			काष्ठा पूर्णांकel_pt_pkt *packet, क्रमागत पूर्णांकel_pt_pkt_ctx *ctx)
अणु
	पूर्णांक ret;

	ret = पूर्णांकel_pt_करो_get_packet(buf, len, packet, *ctx);
	अगर (ret > 0) अणु
		जबतक (ret < 8 && len > (माप_प्रकार)ret && !buf[ret])
			ret += 1;
		पूर्णांकel_pt_upd_pkt_ctx(packet, ctx);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_pt_pkt_desc(स्थिर काष्ठा पूर्णांकel_pt_pkt *packet, अक्षर *buf,
		      माप_प्रकार buf_len)
अणु
	पूर्णांक ret, i, nr;
	अचिन्हित दीर्घ दीर्घ payload = packet->payload;
	स्थिर अक्षर *name = पूर्णांकel_pt_pkt_name(packet->type);

	चयन (packet->type) अणु
	हाल INTEL_PT_BAD:
	हाल INTEL_PT_PAD:
	हाल INTEL_PT_PSB:
	हाल INTEL_PT_PSBEND:
	हाल INTEL_PT_TRACESTOP:
	हाल INTEL_PT_OVF:
		वापस snम_लिखो(buf, buf_len, "%s", name);
	हाल INTEL_PT_TNT: अणु
		माप_प्रकार blen = buf_len;

		ret = snम_लिखो(buf, blen, "%s ", name);
		अगर (ret < 0)
			वापस ret;
		buf += ret;
		blen -= ret;
		क्रम (i = 0; i < packet->count; i++) अणु
			अगर (payload & BIT63)
				ret = snम_लिखो(buf, blen, "T");
			अन्यथा
				ret = snम_लिखो(buf, blen, "N");
			अगर (ret < 0)
				वापस ret;
			buf += ret;
			blen -= ret;
			payload <<= 1;
		पूर्ण
		ret = snम_लिखो(buf, blen, " (%d)", packet->count);
		अगर (ret < 0)
			वापस ret;
		blen -= ret;
		वापस buf_len - blen;
	पूर्ण
	हाल INTEL_PT_TIP_PGD:
	हाल INTEL_PT_TIP_PGE:
	हाल INTEL_PT_TIP:
	हाल INTEL_PT_FUP:
		अगर (!(packet->count))
			वापस snम_लिखो(buf, buf_len, "%s no ip", name);
		__fallthrough;
	हाल INTEL_PT_CYC:
	हाल INTEL_PT_VMCS:
	हाल INTEL_PT_MTC:
	हाल INTEL_PT_MNT:
	हाल INTEL_PT_CBR:
	हाल INTEL_PT_TSC:
		वापस snम_लिखो(buf, buf_len, "%s 0x%llx", name, payload);
	हाल INTEL_PT_TMA:
		वापस snम_लिखो(buf, buf_len, "%s CTC 0x%x FC 0x%x", name,
				(अचिन्हित)payload, packet->count);
	हाल INTEL_PT_MODE_EXEC:
		वापस snम_लिखो(buf, buf_len, "%s %lld", name, payload);
	हाल INTEL_PT_MODE_TSX:
		वापस snम_लिखो(buf, buf_len, "%s TXAbort:%u InTX:%u",
				name, (अचिन्हित)(payload >> 1) & 1,
				(अचिन्हित)payload & 1);
	हाल INTEL_PT_PIP:
		nr = packet->payload & INTEL_PT_VMX_NR_FLAG ? 1 : 0;
		payload &= ~INTEL_PT_VMX_NR_FLAG;
		ret = snम_लिखो(buf, buf_len, "%s 0x%llx (NR=%d)",
			       name, payload >> 1, nr);
		वापस ret;
	हाल INTEL_PT_PTWRITE:
		वापस snम_लिखो(buf, buf_len, "%s 0x%llx IP:0", name, payload);
	हाल INTEL_PT_PTWRITE_IP:
		वापस snम_लिखो(buf, buf_len, "%s 0x%llx IP:1", name, payload);
	हाल INTEL_PT_BEP:
	हाल INTEL_PT_EXSTOP:
		वापस snम_लिखो(buf, buf_len, "%s IP:0", name);
	हाल INTEL_PT_BEP_IP:
	हाल INTEL_PT_EXSTOP_IP:
		वापस snम_लिखो(buf, buf_len, "%s IP:1", name);
	हाल INTEL_PT_MWAIT:
		वापस snम_लिखो(buf, buf_len, "%s 0x%llx Hints 0x%x Extensions 0x%x",
				name, payload, (अचिन्हित पूर्णांक)(payload & 0xff),
				(अचिन्हित पूर्णांक)((payload >> 32) & 0x3));
	हाल INTEL_PT_PWRE:
		वापस snम_लिखो(buf, buf_len, "%s 0x%llx HW:%u CState:%u Sub-CState:%u",
				name, payload, !!(payload & 0x80),
				(अचिन्हित पूर्णांक)((payload >> 12) & 0xf),
				(अचिन्हित पूर्णांक)((payload >> 8) & 0xf));
	हाल INTEL_PT_PWRX:
		वापस snम_लिखो(buf, buf_len, "%s 0x%llx Last CState:%u Deepest CState:%u Wake Reason 0x%x",
				name, payload,
				(अचिन्हित पूर्णांक)((payload >> 4) & 0xf),
				(अचिन्हित पूर्णांक)(payload & 0xf),
				(अचिन्हित पूर्णांक)((payload >> 8) & 0xf));
	हाल INTEL_PT_BBP:
		वापस snम_लिखो(buf, buf_len, "%s SZ %s-byte Type 0x%llx",
				name, packet->count ? "4" : "8", payload);
	हाल INTEL_PT_BIP:
		वापस snम_लिखो(buf, buf_len, "%s ID 0x%02x Value 0x%llx",
				name, packet->count, payload);
	शेष:
		अवरोध;
	पूर्ण
	वापस snम_लिखो(buf, buf_len, "%s 0x%llx (%d)",
			name, payload, packet->count);
पूर्ण
