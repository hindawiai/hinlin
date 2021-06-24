<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * conmakehash.c
 *
 * Create arrays क्रम initializing the kernel folded tables (using a hash
 * table turned out to be to limiting...)  Unक्रमtunately we can't simply
 * preinitialize the tables at compile समय since kमुक्त() cannot accept
 * memory not allocated by kदो_स्मृति(), and करोing our own memory management
 * just क्रम this seems like massive overसमाप्त.
 *
 * Copyright (C) 1995-1997 H. Peter Anvin
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sysनिकासs.h>
#समावेश <माला.स>
#समावेश <प्रकार.स>

#घोषणा MAX_FONTLEN 256

प्रकार अचिन्हित लघु unicode;

अटल व्योम usage(अक्षर *argv0)
अणु
  ख_लिखो(मानक_त्रुटि, "Usage: \n"
         "        %s chartable [hashsize] [hashstep] [maxhashlevel]\n", argv0);
  निकास(EX_USAGE);
पूर्ण

अटल पूर्णांक getunicode(अक्षर **p0)
अणु
  अक्षर *p = *p0;

  जबतक (*p == ' ' || *p == '\t')
    p++;
  अगर (*p != 'U' || p[1] != '+' ||
      !है_षष्ठादशक(p[2]) || !है_षष्ठादशक(p[3]) || !है_षष्ठादशक(p[4]) ||
      !है_षष्ठादशक(p[5]) || है_षष्ठादशक(p[6]))
    वापस -1;
  *p0 = p+6;
  वापस म_से_दीर्घ(p+2,0,16);
पूर्ण

unicode unitable[MAX_FONTLEN][255];
				/* Massive overसमाप्त, but who cares? */
पूर्णांक unicount[MAX_FONTLEN];

अटल व्योम addpair(पूर्णांक fp, पूर्णांक un)
अणु
  पूर्णांक i;

  अगर ( un <= 0xfffe )
    अणु
      /* Check it isn't a duplicate */

      क्रम ( i = 0 ; i < unicount[fp] ; i++ )
	अगर ( unitable[fp][i] == un )
	  वापस;

      /* Add to list */

      अगर ( unicount[fp] > 254 )
	अणु
	  ख_लिखो(मानक_त्रुटि, "ERROR: Only 255 unicodes/glyph permitted!\n");
	  निकास(EX_DATAERR);
	पूर्ण

      unitable[fp][unicount[fp]] = un;
      unicount[fp]++;
    पूर्ण

  /* otherwise: ignore */
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
  खाता *ctbl;
  अक्षर *tblname;
  अक्षर buffer[65536];
  पूर्णांक fontlen;
  पूर्णांक i, nuni, nent;
  पूर्णांक fp0, fp1, un0, un1;
  अक्षर *p, *p1;

  अगर ( argc < 2 || argc > 5 )
    usage(argv[0]);

  अगर ( !म_भेद(argv[1],"-") )
    अणु
      ctbl = मानक_निवेश;
      tblname = "stdin";
    पूर्ण
  अन्यथा
    अणु
      ctbl = ख_खोलो(tblname = argv[1], "r");
      अगर ( !ctbl )
	अणु
	  लिखो_त्रुटि(tblname);
	  निकास(EX_NOINPUT);
	पूर्ण
    पूर्ण

  /* For now we assume the शेष font is always 256 अक्षरacters. */
  fontlen = 256;

  /* Initialize table */

  क्रम ( i = 0 ; i < fontlen ; i++ )
    unicount[i] = 0;

  /* Now we come to the tricky part.  Parse the input table. */

  जबतक ( ख_माला_लो(buffer, माप(buffer), ctbl) != शून्य )
    अणु
      अगर ( (p = म_अक्षर(buffer, '\n')) != शून्य )
	*p = '\0';
      अन्यथा
	ख_लिखो(मानक_त्रुटि, "%s: Warning: line too long\n", tblname);

      p = buffer;

/*
 * Syntax accepted:
 *	<fontpos>	<unicode> <unicode> ...
 *	<range>		idem
 *	<range>		<unicode range>
 *
 * where <range> ::= <fontpos>-<fontpos>
 * and <unicode> ::= U+<h><h><h><h>
 * and <h> ::= <hexadecimal digit>
 */

      जबतक (*p == ' ' || *p == '\t')
	p++;
      अगर (!*p || *p == '#')
	जारी;	/* skip comment or blank line */

      fp0 = म_से_दीर्घ(p, &p1, 0);
      अगर (p1 == p)
	अणु
	  ख_लिखो(मानक_त्रुटि, "Bad input line: %s\n", buffer);
	  निकास(EX_DATAERR);
        पूर्ण
      p = p1;

      जबतक (*p == ' ' || *p == '\t')
	p++;
      अगर (*p == '-')
	अणु
	  p++;
	  fp1 = म_से_दीर्घ(p, &p1, 0);
	  अगर (p1 == p)
	    अणु
	      ख_लिखो(मानक_त्रुटि, "Bad input line: %s\n", buffer);
	      निकास(EX_DATAERR);
	    पूर्ण
	  p = p1;
        पूर्ण
      अन्यथा
	fp1 = 0;

      अगर ( fp0 < 0 || fp0 >= fontlen )
	अणु
	    ख_लिखो(मानक_त्रुटि,
		    "%s: Glyph number (0x%x) larger than font length\n",
		    tblname, fp0);
	    निकास(EX_DATAERR);
	पूर्ण
      अगर ( fp1 && (fp1 < fp0 || fp1 >= fontlen) )
	अणु
	    ख_लिखो(मानक_त्रुटि,
		    "%s: Bad end of range (0x%x)\n",
		    tblname, fp1);
	    निकास(EX_DATAERR);
	पूर्ण

      अगर (fp1)
	अणु
	  /* we have a range; expect the word "idem" or a Unicode range of the
	     same length */
	  जबतक (*p == ' ' || *p == '\t')
	    p++;
	  अगर (!म_भेदन(p, "idem", 4))
	    अणु
	      क्रम (i=fp0; i<=fp1; i++)
		addpair(i,i);
	      p += 4;
	    पूर्ण
	  अन्यथा
	    अणु
	      un0 = getunicode(&p);
	      जबतक (*p == ' ' || *p == '\t')
		p++;
	      अगर (*p != '-')
		अणु
		  ख_लिखो(मानक_त्रुटि,
"%s: Corresponding to a range of font positions, there should be a Unicode range\n",
			  tblname);
		  निकास(EX_DATAERR);
	        पूर्ण
	      p++;
	      un1 = getunicode(&p);
	      अगर (un0 < 0 || un1 < 0)
		अणु
		  ख_लिखो(मानक_त्रुटि,
"%s: Bad Unicode range corresponding to font position range 0x%x-0x%x\n",
			  tblname, fp0, fp1);
		  निकास(EX_DATAERR);
	        पूर्ण
	      अगर (un1 - un0 != fp1 - fp0)
		अणु
		  ख_लिखो(मानक_त्रुटि,
"%s: Unicode range U+%x-U+%x not of the same length as font position range 0x%x-0x%x\n",
			  tblname, un0, un1, fp0, fp1);
		  निकास(EX_DATAERR);
	        पूर्ण
	      क्रम(i=fp0; i<=fp1; i++)
		addpair(i,un0-fp0+i);
	    पूर्ण
        पूर्ण
      अन्यथा
	अणु
	    /* no range; expect a list of unicode values क्रम a single font position */

	    जबतक ( (un0 = getunicode(&p)) >= 0 )
	      addpair(fp0, un0);
	पूर्ण
      जबतक (*p == ' ' || *p == '\t')
	p++;
      अगर (*p && *p != '#')
	ख_लिखो(मानक_त्रुटि, "%s: trailing junk (%s) ignored\n", tblname, p);
    पूर्ण

  /* Okay, we hit खातापूर्ण, now output hash table */

  ख_बंद(ctbl);


  /* Compute total size of Unicode list */
  nuni = 0;
  क्रम ( i = 0 ; i < fontlen ; i++ )
    nuni += unicount[i];

  म_लिखो("\
/*\न\
 * Do not edit this file; it was स्वतःmatically generated by\न\
 *\न\
 * conmakehash %s > [this file]\न\
 *\न\
 */\न\
\न\
#समावेश <linux/types.h>\न\
\न\
u8 dfont_unicount[%d] = \न\
अणु\न\ट", argv[1], fontlen);

  क्रम ( i = 0 ; i < fontlen ; i++ )
    अणु
      म_लिखो("%3d", unicount[i]);
      अगर ( i == fontlen-1 )
        म_लिखो("\n};\n");
      अन्यथा अगर ( i % 8 == 7 )
        म_लिखो(",\n\t");
      अन्यथा
        म_लिखो(", ");
    पूर्ण

  म_लिखो("\nu16 dfont_unitable[%d] = \n{\n\t", nuni);

  fp0 = 0;
  nent = 0;
  क्रम ( i = 0 ; i < nuni ; i++ )
    अणु
      जबतक ( nent >= unicount[fp0] )
	अणु
	  fp0++;
	  nent = 0;
	पूर्ण
      म_लिखो("0x%04x", unitable[fp0][nent++]);
      अगर ( i == nuni-1 )
         म_लिखो("\n};\n");
       अन्यथा अगर ( i % 8 == 7 )
         म_लिखो(",\n\t");
       अन्यथा
         म_लिखो(", ");
    पूर्ण

  निकास(EX_OK);
पूर्ण
