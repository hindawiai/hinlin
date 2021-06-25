<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "list.h"
#समावेश "nosy-dump.h"

#घोषणा CSR_FCP_COMMAND			0xfffff0000b00ull
#घोषणा CSR_FCP_RESPONSE		0xfffff0000d00ull

अटल स्थिर अक्षर * स्थिर ctype_names[] = अणु
	[0x0] = "control",		[0x8] = "not implemented",
	[0x1] = "status",		[0x9] = "accepted",
	[0x2] = "specific inquiry",	[0xa] = "rejected",
	[0x3] = "notify",		[0xb] = "in transition",
	[0x4] = "general inquiry",	[0xc] = "stable",
	[0x5] = "(reserved 0x05)",	[0xd] = "changed",
	[0x6] = "(reserved 0x06)",	[0xe] = "(reserved 0x0e)",
	[0x7] = "(reserved 0x07)",	[0xf] = "interim",
पूर्ण;

अटल स्थिर अक्षर * स्थिर subunit_type_names[] = अणु
	[0x00] = "monitor",		[0x10] = "(reserved 0x10)",
	[0x01] = "audio",		[0x11] = "(reserved 0x11)",
	[0x02] = "printer",		[0x12] = "(reserved 0x12)",
	[0x03] = "disc",		[0x13] = "(reserved 0x13)",
	[0x04] = "tape recorder/player",[0x14] = "(reserved 0x14)",
	[0x05] = "tuner",		[0x15] = "(reserved 0x15)",
	[0x06] = "ca",			[0x16] = "(reserved 0x16)",
	[0x07] = "camera",		[0x17] = "(reserved 0x17)",
	[0x08] = "(reserved 0x08)",	[0x18] = "(reserved 0x18)",
	[0x09] = "panel",		[0x19] = "(reserved 0x19)",
	[0x0a] = "bulletin board",	[0x1a] = "(reserved 0x1a)",
	[0x0b] = "camera storage",	[0x1b] = "(reserved 0x1b)",
	[0x0c] = "(reserved 0x0c)",	[0x1c] = "vendor unique",
	[0x0d] = "(reserved 0x0d)",	[0x1d] = "all subunit types",
	[0x0e] = "(reserved 0x0e)",	[0x1e] = "subunit_type extended to next byte",
	[0x0f] = "(reserved 0x0f)",	[0x1f] = "unit",
पूर्ण;

काष्ठा avc_क्रमागत अणु
	पूर्णांक value;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा avc_field अणु
	स्थिर अक्षर *name;	/* Short name क्रम field. */
	पूर्णांक offset;		/* Location of field, specअगरied in bits; */
				/* negative means from end of packet.    */
	पूर्णांक width;		/* Width of field, 0 means use data_length. */
	काष्ठा avc_क्रमागत *names;
पूर्ण;

काष्ठा avc_opcode_info अणु
	स्थिर अक्षर *name;
	काष्ठा avc_field fields[8];
पूर्ण;

काष्ठा avc_क्रमागत घातer_field_names[] = अणु
	अणु 0x70, "on" पूर्ण,
	अणु 0x60, "off" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा avc_opcode_info opcode_info[256] = अणु

	/* TA Document 1999026 */
	/* AV/C Digital Interface Command Set General Specअगरication 4.0 */
	[0xb2] = अणु "power", अणु
			अणु "state", 0, 8, घातer_field_names पूर्ण
		पूर्ण
	पूर्ण,
	[0x30] = अणु "unit info", अणु
			अणु "foo", 0, 8 पूर्ण,
			अणु "unit_type", 8, 5 पूर्ण,
			अणु "unit", 13, 3 पूर्ण,
			अणु "company id", 16, 24 पूर्ण,
		पूर्ण
	पूर्ण,
	[0x31] = अणु "subunit info" पूर्ण,
	[0x01] = अणु "reserve" पूर्ण,
	[0xb0] = अणु "version" पूर्ण,
	[0x00] = अणु "vendor dependent" पूर्ण,
	[0x02] = अणु "plug info" पूर्ण,
	[0x12] = अणु "channel usage" पूर्ण,
	[0x24] = अणु "connect" पूर्ण,
	[0x20] = अणु "connect av" पूर्ण,
	[0x22] = अणु "connections" पूर्ण,
	[0x11] = अणु "digital input" पूर्ण,
	[0x10] = अणु "digital output" पूर्ण,
	[0x25] = अणु "disconnect" पूर्ण,
	[0x21] = अणु "disconnect av" पूर्ण,
	[0x19] = अणु "input plug signal format" पूर्ण,
	[0x18] = अणु "output plug signal format" पूर्ण,
	[0x1f] = अणु "general bus setup" पूर्ण,

	/* TA Document 1999025 */
	/* AV/C Descriptor Mechanism Specअगरication Version 1.0 */
	[0x0c] = अणु "create descriptor" पूर्ण,
	[0x08] = अणु "open descriptor" पूर्ण,
	[0x09] = अणु "read descriptor" पूर्ण,
	[0x0a] = अणु "write descriptor" पूर्ण,
	[0x05] = अणु "open info block" पूर्ण,
	[0x06] = अणु "read info block" पूर्ण,
	[0x07] = अणु "write info block" पूर्ण,
	[0x0b] = अणु "search descriptor" पूर्ण,
	[0x0d] = अणु "object number select" पूर्ण,

	/* TA Document 1999015 */
	/* AV/C Command Set क्रम Rate Control of Isochronous Data Flow 1.0 */
	[0xb3] = अणु "rate", अणु
			अणु "subfunction", 0, 8 पूर्ण,
			अणु "result", 8, 8 पूर्ण,
			अणु "plug_type", 16, 8 पूर्ण,
			अणु "plug_id", 16, 8 पूर्ण,
		पूर्ण
	पूर्ण,

	/* TA Document 1999008 */
	/* AV/C Audio Subunit Specअगरication 1.0 */
	[0xb8] = अणु "function block" पूर्ण,

	/* TA Document 2001001 */
	/* AV/C Panel Subunit Specअगरication 1.1 */
	[0x7d] = अणु "gui update" पूर्ण,
	[0x7e] = अणु "push gui data" पूर्ण,
	[0x7f] = अणु "user action" पूर्ण,
	[0x7c] = अणु "pass through" पूर्ण,

	/* */
	[0x26] = अणु "asynchronous connection" पूर्ण,
पूर्ण;

काष्ठा avc_frame अणु
	uपूर्णांक32_t opeअक्रम0:8;
	uपूर्णांक32_t opcode:8;
	uपूर्णांक32_t subunit_id:3;
	uपूर्णांक32_t subunit_type:5;
	uपूर्णांक32_t ctype:4;
	uपूर्णांक32_t cts:4;
पूर्ण;

अटल व्योम
decode_avc(काष्ठा link_transaction *t)
अणु
	काष्ठा avc_frame *frame =
	    (काष्ठा avc_frame *) t->request->packet.ग_लिखो_block.data;
	स्थिर काष्ठा avc_opcode_info *info;
	स्थिर अक्षर *name;
	अक्षर buffer[32];
	पूर्णांक i;

	info = &opcode_info[frame->opcode];
	अगर (info->name == शून्य) अणु
		snम_लिखो(buffer, माप(buffer),
			 "(unknown opcode 0x%02x)", frame->opcode);
		name = buffer;
	पूर्ण अन्यथा अणु
		name = info->name;
	पूर्ण

	म_लिखो("av/c %s, subunit_type=%s, subunit_id=%d, opcode=%s",
	    ctype_names[frame->ctype], subunit_type_names[frame->subunit_type],
	    frame->subunit_id, name);

	क्रम (i = 0; info->fields[i].name != शून्य; i++)
		म_लिखो(", %s", info->fields[i].name);

	म_लिखो("\n");
पूर्ण

पूर्णांक
decode_fcp(काष्ठा link_transaction *t)
अणु
	काष्ठा avc_frame *frame =
	    (काष्ठा avc_frame *) t->request->packet.ग_लिखो_block.data;
	अचिन्हित दीर्घ दीर्घ offset =
	    ((अचिन्हित दीर्घ दीर्घ) t->request->packet.common.offset_high << 32) |
	    t->request->packet.common.offset_low;

	अगर (t->request->packet.common.tcode != TCODE_WRITE_BLOCK_REQUEST)
		वापस 0;

	अगर (offset == CSR_FCP_COMMAND || offset == CSR_FCP_RESPONSE) अणु
		चयन (frame->cts) अणु
		हाल 0x00:
			decode_avc(t);
			अवरोध;
		हाल 0x01:
			म_लिखो("cal fcp frame (cts=0x01)\n");
			अवरोध;
		हाल 0x02:
			म_लिखो("ehs fcp frame (cts=0x02)\n");
			अवरोध;
		हाल 0x03:
			म_लिखो("havi fcp frame (cts=0x03)\n");
			अवरोध;
		हाल 0x0e:
			म_लिखो("vendor specific fcp frame (cts=0x0e)\n");
			अवरोध;
		हाल 0x0f:
			म_लिखो("extended cts\n");
			अवरोध;
		शेष:
			म_लिखो("reserved fcp frame (ctx=0x%02x)\n", frame->cts);
			अवरोध;
		पूर्ण
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

