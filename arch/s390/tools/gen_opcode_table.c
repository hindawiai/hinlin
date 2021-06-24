<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generate opcode table initializers क्रम the in-kernel disassembler.
 *
 *    Copyright IBM Corp. 2017
 *
 */

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <मानकपन.स>

#घोषणा STRING_SIZE_MAX 20

काष्ठा insn_type अणु
	अचिन्हित अक्षर byte;
	अचिन्हित अक्षर mask;
	अक्षर **क्रमmat;
पूर्ण;

काष्ठा insn अणु
	काष्ठा insn_type *type;
	अक्षर opcode[STRING_SIZE_MAX];
	अक्षर name[STRING_SIZE_MAX];
	अक्षर upper[STRING_SIZE_MAX];
	अक्षर क्रमmat[STRING_SIZE_MAX];
	अचिन्हित पूर्णांक name_len;
पूर्ण;

काष्ठा insn_group अणु
	काष्ठा insn_type *type;
	पूर्णांक offset;
	पूर्णांक count;
	अक्षर opcode[2];
पूर्ण;

काष्ठा insn_क्रमmat अणु
	अक्षर *क्रमmat;
	पूर्णांक type;
पूर्ण;

काष्ठा gen_opcode अणु
	काष्ठा insn *insn;
	पूर्णांक nr;
	काष्ठा insn_group *group;
	पूर्णांक nr_groups;
पूर्ण;

/*
 * Table of inकाष्ठाion क्रमmat types. Each opcode is defined with at
 * least one byte (two nibbles), three nibbles, or two bytes (four
 * nibbles).
 * The byte member of each inकाष्ठाion क्रमmat type entry defines
 * within which byte of an inकाष्ठाion the third (and fourth) nibble
 * of an opcode can be found. The mask member is the and-mask that
 * needs to be applied on this byte in order to get the third (and
 * fourth) nibble of the opcode.
 * The क्रमmat array defines all inकाष्ठाion क्रमmats (as defined in the
 * Principles of Operation) which have the same position of the opcode
 * nibbles.
 * A special हाल are inकाष्ठाion क्रमmats with 1-byte opcodes. In this
 * हाल the byte member always is zero, so that the mask is applied on
 * the (only) byte that contains the opcode.
 */
अटल काष्ठा insn_type insn_type_table[] = अणु
	अणु
		.byte = 0,
		.mask = 0xff,
		.क्रमmat = (अक्षर *[]) अणु
			"MII",
			"RR",
			"RS",
			"RSI",
			"RX",
			"SI",
			"SMI",
			"SS",
			शून्य,
		पूर्ण,
	पूर्ण,
	अणु
		.byte = 1,
		.mask = 0x0f,
		.क्रमmat = (अक्षर *[]) अणु
			"RI",
			"RIL",
			"SSF",
			शून्य,
		पूर्ण,
	पूर्ण,
	अणु
		.byte = 1,
		.mask = 0xff,
		.क्रमmat = (अक्षर *[]) अणु
			"E",
			"IE",
			"RRE",
			"RRF",
			"RRR",
			"S",
			"SIL",
			"SSE",
			शून्य,
		पूर्ण,
	पूर्ण,
	अणु
		.byte = 5,
		.mask = 0xff,
		.क्रमmat = (अक्षर *[]) अणु
			"RIE",
			"RIS",
			"RRS",
			"RSE",
			"RSL",
			"RSY",
			"RXE",
			"RXF",
			"RXY",
			"SIY",
			"VRI",
			"VRR",
			"VRS",
			"VRV",
			"VRX",
			"VSI",
			शून्य,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा insn_type *insn_क्रमmat_to_type(अक्षर *क्रमmat)
अणु
	अक्षर पंचांगp[STRING_SIZE_MAX];
	अक्षर *base_क्रमmat, **ptr;
	पूर्णांक i;

	म_नकल(पंचांगp, क्रमmat);
	base_क्रमmat = पंचांगp;
	base_क्रमmat = strsep(&base_क्रमmat, "_");
	क्रम (i = 0; i < माप(insn_type_table) / माप(insn_type_table[0]); i++) अणु
		ptr = insn_type_table[i].क्रमmat;
		जबतक (*ptr) अणु
			अगर (!म_भेद(base_क्रमmat, *ptr))
				वापस &insn_type_table[i];
			ptr++;
		पूर्ण
	पूर्ण
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम पढ़ो_inकाष्ठाions(काष्ठा gen_opcode *desc)
अणु
	काष्ठा insn insn;
	पूर्णांक rc, i;

	जबतक (1) अणु
		rc = म_पूछो("%s %s %s", insn.opcode, insn.name, insn.क्रमmat);
		अगर (rc == खातापूर्ण)
			अवरोध;
		अगर (rc != 3)
			निकास(निकास_त्रुटि);
		insn.type = insn_क्रमmat_to_type(insn.क्रमmat);
		insn.name_len = म_माप(insn.name);
		क्रम (i = 0; i <= insn.name_len; i++)
			insn.upper[i] = बड़े((अचिन्हित अक्षर)insn.name[i]);
		desc->nr++;
		desc->insn = पुनः_स्मृति(desc->insn, desc->nr * माप(*desc->insn));
		अगर (!desc->insn)
			निकास(निकास_त्रुटि);
		desc->insn[desc->nr - 1] = insn;
	पूर्ण
पूर्ण

अटल पूर्णांक cmpक्रमmat(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस म_भेद(((काष्ठा insn *)a)->क्रमmat, ((काष्ठा insn *)b)->क्रमmat);
पूर्ण

अटल व्योम prपूर्णांक_क्रमmats(काष्ठा gen_opcode *desc)
अणु
	अक्षर *क्रमmat;
	पूर्णांक i, count;

	क्विक(desc->insn, desc->nr, माप(*desc->insn), cmpक्रमmat);
	क्रमmat = "";
	count = 0;
	म_लिखो("enum {\n");
	क्रम (i = 0; i < desc->nr; i++) अणु
		अगर (!म_भेद(क्रमmat, desc->insn[i].क्रमmat))
			जारी;
		count++;
		क्रमmat = desc->insn[i].क्रमmat;
		म_लिखो("\tINSTR_%s,\n", क्रमmat);
	पूर्ण
	म_लिखो("}; /* %d */\n\n", count);
पूर्ण

अटल पूर्णांक cmp_दीर्घ_insn(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस म_भेद(((काष्ठा insn *)a)->name, ((काष्ठा insn *)b)->name);
पूर्ण

अटल व्योम prपूर्णांक_दीर्घ_insn(काष्ठा gen_opcode *desc)
अणु
	काष्ठा insn *insn;
	पूर्णांक i, count;

	क्विक(desc->insn, desc->nr, माप(*desc->insn), cmp_दीर्घ_insn);
	count = 0;
	म_लिखो("enum {\n");
	क्रम (i = 0; i < desc->nr; i++) अणु
		insn = &desc->insn[i];
		अगर (insn->name_len < 6)
			जारी;
		म_लिखो("\tLONG_INSN_%s,\n", insn->upper);
		count++;
	पूर्ण
	म_लिखो("}; /* %d */\n\n", count);

	म_लिखो("#define LONG_INSN_INITIALIZER { \\\n");
	क्रम (i = 0; i < desc->nr; i++) अणु
		insn = &desc->insn[i];
		अगर (insn->name_len < 6)
			जारी;
		म_लिखो("\t[LONG_INSN_%s] = \"%s\", \\\n", insn->upper, insn->name);
	पूर्ण
	म_लिखो("}\n\n");
पूर्ण

अटल व्योम prपूर्णांक_opcode(काष्ठा insn *insn, पूर्णांक nr)
अणु
	अक्षर *opcode;

	opcode = insn->opcode;
	अगर (insn->type->byte != 0)
		opcode += 2;
	म_लिखो("\t[%4d] = { .opfrag = 0x%s, .format = INSTR_%s, ", nr, opcode, insn->क्रमmat);
	अगर (insn->name_len < 6)
		म_लिखो(".name = \"%s\" ", insn->name);
	अन्यथा
		म_लिखो(".offset = LONG_INSN_%s ", insn->upper);
	म_लिखो("}, \\\n");
पूर्ण

अटल व्योम add_to_group(काष्ठा gen_opcode *desc, काष्ठा insn *insn, पूर्णांक offset)
अणु
	काष्ठा insn_group *group;

	group = desc->group ? &desc->group[desc->nr_groups - 1] : शून्य;
	अगर (group && (!म_भेदन(group->opcode, insn->opcode, 2) || group->type->byte == 0)) अणु
		group->count++;
		वापस;
	पूर्ण
	desc->nr_groups++;
	desc->group = पुनः_स्मृति(desc->group, desc->nr_groups * माप(*desc->group));
	अगर (!desc->group)
		निकास(निकास_त्रुटि);
	group = &desc->group[desc->nr_groups - 1];
	स_नकल(group->opcode, insn->opcode, 2);
	group->type = insn->type;
	group->offset = offset;
	group->count = 1;
पूर्ण

अटल पूर्णांक cmpopcode(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस म_भेद(((काष्ठा insn *)a)->opcode, ((काष्ठा insn *)b)->opcode);
पूर्ण

अटल व्योम prपूर्णांक_opcode_table(काष्ठा gen_opcode *desc)
अणु
	अक्षर opcode[2] = "";
	काष्ठा insn *insn;
	पूर्णांक i, offset;

	क्विक(desc->insn, desc->nr, माप(*desc->insn), cmpopcode);
	म_लिखो("#define OPCODE_TABLE_INITIALIZER { \\\n");
	offset = 0;
	क्रम (i = 0; i < desc->nr; i++) अणु
		insn = &desc->insn[i];
		अगर (insn->type->byte == 0)
			जारी;
		add_to_group(desc, insn, offset);
		अगर (म_भेदन(opcode, insn->opcode, 2)) अणु
			स_नकल(opcode, insn->opcode, 2);
			म_लिखो("\t/* %.2s */ \\\n", opcode);
		पूर्ण
		prपूर्णांक_opcode(insn, offset);
		offset++;
	पूर्ण
	म_लिखो("\t/* 1-byte opcode instructions */ \\\n");
	क्रम (i = 0; i < desc->nr; i++) अणु
		insn = &desc->insn[i];
		अगर (insn->type->byte != 0)
			जारी;
		add_to_group(desc, insn, offset);
		prपूर्णांक_opcode(insn, offset);
		offset++;
	पूर्ण
	म_लिखो("}\n\n");
पूर्ण

अटल व्योम prपूर्णांक_opcode_table_offsets(काष्ठा gen_opcode *desc)
अणु
	काष्ठा insn_group *group;
	पूर्णांक i;

	म_लिखो("#define OPCODE_OFFSET_INITIALIZER { \\\n");
	क्रम (i = 0; i < desc->nr_groups; i++) अणु
		group = &desc->group[i];
		म_लिखो("\t{ .opcode = 0x%.2s, .mask = 0x%02x, .byte = %d, .offset = %d, .count = %d }, \\\n",
		       group->opcode, group->type->mask, group->type->byte, group->offset, group->count);
	पूर्ण
	म_लिखो("}\n\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा gen_opcode _desc = अणु 0 पूर्ण;
	काष्ठा gen_opcode *desc = &_desc;

	पढ़ो_inकाष्ठाions(desc);
	म_लिखो("#ifndef __S390_GENERATED_DIS_DEFS_H__\n");
	म_लिखो("#define __S390_GENERATED_DIS_DEFS_H__\n");
	म_लिखो("/*\n");
	म_लिखो(" * DO NOT MODIFY.\n");
	म_लिखो(" *\n");
	म_लिखो(" * This file was generated by %s\n", __खाता__);
	म_लिखो(" */\n\n");
	prपूर्णांक_क्रमmats(desc);
	prपूर्णांक_दीर्घ_insn(desc);
	prपूर्णांक_opcode_table(desc);
	prपूर्णांक_opcode_table_offsets(desc);
	म_लिखो("#endif\n");
	निकास(निकास_सफल);
पूर्ण
