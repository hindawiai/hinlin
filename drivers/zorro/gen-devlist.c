<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Generate devlist.h from the Zorro ID file.
 *
 *	(c) 2000 Geert Uytterhoeven <geert@linux-m68k.org>
 *
 *	Based on the PCI version:
 *
 *	(c) 1999--2000 Martin Mares <mj@ucw.cz>
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>

#घोषणा MAX_NAME_SIZE 63

अटल व्योम
pq(खाता *f, स्थिर अक्षर *c)
अणु
	जबतक (*c) अणु
		अगर (*c == '"')
			ख_लिखो(f, "\\\"");
		अन्यथा
			ख_अक्षर_दो(*c, f);
		c++;
	पूर्ण
पूर्ण

पूर्णांक
मुख्य(व्योम)
अणु
	अक्षर line[1024], *c, *bra, manuf[8];
	पूर्णांक manufs = 0;
	पूर्णांक mode = 0;
	पूर्णांक lino = 0;
	पूर्णांक manuf_len = 0;
	खाता *devf;

	devf = ख_खोलो("devlist.h", "w");
	अगर (!devf) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot create output file!\n");
		वापस 1;
	पूर्ण

	जबतक (ख_माला_लो(line, माप(line)-1, मानक_निवेश)) अणु
		lino++;
		अगर ((c = म_अक्षर(line, '\n')))
			*c = 0;
		अगर (!line[0] || line[0] == '#')
			जारी;
		अगर (line[0] == '\t') अणु
			चयन (mode) अणु
			हाल 1:
				अगर (म_माप(line) > 5 && line[5] == ' ') अणु
					c = line + 5;
					जबतक (*c == ' ')
						*c++ = 0;
					अगर (manuf_len + म_माप(c) + 1 > MAX_NAME_SIZE) अणु
						/* Too दीर्घ, try cutting off दीर्घ description */
						bra = म_अक्षर(c, '[');
						अगर (bra && bra > c && bra[-1] == ' ')
							bra[-1] = 0;
						अगर (manuf_len + म_माप(c) + 1 > MAX_NAME_SIZE) अणु
							ख_लिखो(मानक_त्रुटि, "Line %d: Product name too long\n", lino);
							वापस 1;
						पूर्ण
					पूर्ण
					ख_लिखो(devf, "\tPRODUCT(%s,%s,\"", manuf, line+1);
					pq(devf, c);
					ख_माला_दो("\")\n", devf);
				पूर्ण अन्यथा जाओ err;
				अवरोध;
			शेष:
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अगर (म_माप(line) > 4 && line[4] == ' ') अणु
			c = line + 4;
			जबतक (*c == ' ')
				*c++ = 0;
			अगर (manufs)
				ख_माला_दो("ENDMANUF()\n\n", devf);
			manufs++;
			म_नकल(manuf, line);
			manuf_len = म_माप(c);
			अगर (manuf_len + 24 > MAX_NAME_SIZE) अणु
				ख_लिखो(मानक_त्रुटि, "Line %d: manufacturer name too long\n", lino);
				वापस 1;
			पूर्ण
			ख_लिखो(devf, "MANUF(%s,\"", manuf);
			pq(devf, c);
			ख_माला_दो("\")\n", devf);
			mode = 1;
		पूर्ण अन्यथा अणु
		err:
			ख_लिखो(मानक_त्रुटि, "Line %d: Syntax error in mode %d: %s\n", lino, mode, line);
			वापस 1;
		पूर्ण
	पूर्ण
	ख_माला_दो("ENDMANUF()\न\
\न\
#अघोषित MANUF\न\
#अघोषित PRODUCT\न\
#अघोषित ENDMANUF\न", devf);

	ख_बंद(devf);

	वापस 0;
पूर्ण
