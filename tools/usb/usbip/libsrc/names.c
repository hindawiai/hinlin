<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      names.c  --  USB name database manipulation routines
 *
 *      Copyright (C) 1999, 2000  Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *	Copyright (C) 2005 Takahiro Hirofuchi
 *		- names_deinit() is added.
 */

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <dirent.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <प्रकार.स>

#समावेश "names.h"
#समावेश "usbip_common.h"

काष्ठा venकरोr अणु
	काष्ठा venकरोr *next;
	u_पूर्णांक16_t venकरोrid;
	अक्षर name[1];
पूर्ण;

काष्ठा product अणु
	काष्ठा product *next;
	u_पूर्णांक16_t venकरोrid, productid;
	अक्षर name[1];
पूर्ण;

काष्ठा class अणु
	काष्ठा class *next;
	u_पूर्णांक8_t classid;
	अक्षर name[1];
पूर्ण;

काष्ठा subclass अणु
	काष्ठा subclass *next;
	u_पूर्णांक8_t classid, subclassid;
	अक्षर name[1];
पूर्ण;

काष्ठा protocol अणु
	काष्ठा protocol *next;
	u_पूर्णांक8_t classid, subclassid, protocolid;
	अक्षर name[1];
पूर्ण;

काष्ठा genericstrtable अणु
	काष्ठा genericstrtable *next;
	अचिन्हित पूर्णांक num;
	अक्षर name[1];
पूर्ण;


#घोषणा HASH1  0x10
#घोषणा HASH2  0x02
#घोषणा HASHSZ 16

अटल अचिन्हित पूर्णांक hashnum(अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक mask1 = HASH1 << 27, mask2 = HASH2 << 27;

	क्रम (; mask1 >= HASH1; mask1 >>= 1, mask2 >>= 1)
		अगर (num & mask1)
			num ^= mask2;
	वापस num & (HASHSZ-1);
पूर्ण


अटल काष्ठा venकरोr *venकरोrs[HASHSZ] = अणु शून्य, पूर्ण;
अटल काष्ठा product *products[HASHSZ] = अणु शून्य, पूर्ण;
अटल काष्ठा class *classes[HASHSZ] = अणु शून्य, पूर्ण;
अटल काष्ठा subclass *subclasses[HASHSZ] = अणु शून्य, पूर्ण;
अटल काष्ठा protocol *protocols[HASHSZ] = अणु शून्य, पूर्ण;

स्थिर अक्षर *names_venकरोr(u_पूर्णांक16_t venकरोrid)
अणु
	काष्ठा venकरोr *v;

	v = venकरोrs[hashnum(venकरोrid)];
	क्रम (; v; v = v->next)
		अगर (v->venकरोrid == venकरोrid)
			वापस v->name;
	वापस शून्य;
पूर्ण

स्थिर अक्षर *names_product(u_पूर्णांक16_t venकरोrid, u_पूर्णांक16_t productid)
अणु
	काष्ठा product *p;

	p = products[hashnum((venकरोrid << 16) | productid)];
	क्रम (; p; p = p->next)
		अगर (p->venकरोrid == venकरोrid && p->productid == productid)
			वापस p->name;
	वापस शून्य;
पूर्ण

स्थिर अक्षर *names_class(u_पूर्णांक8_t classid)
अणु
	काष्ठा class *c;

	c = classes[hashnum(classid)];
	क्रम (; c; c = c->next)
		अगर (c->classid == classid)
			वापस c->name;
	वापस शून्य;
पूर्ण

स्थिर अक्षर *names_subclass(u_पूर्णांक8_t classid, u_पूर्णांक8_t subclassid)
अणु
	काष्ठा subclass *s;

	s = subclasses[hashnum((classid << 8) | subclassid)];
	क्रम (; s; s = s->next)
		अगर (s->classid == classid && s->subclassid == subclassid)
			वापस s->name;
	वापस शून्य;
पूर्ण

स्थिर अक्षर *names_protocol(u_पूर्णांक8_t classid, u_पूर्णांक8_t subclassid,
			   u_पूर्णांक8_t protocolid)
अणु
	काष्ठा protocol *p;

	p = protocols[hashnum((classid << 16) | (subclassid << 8)
			      | protocolid)];
	क्रम (; p; p = p->next)
		अगर (p->classid == classid && p->subclassid == subclassid &&
		    p->protocolid == protocolid)
			वापस p->name;
	वापस शून्य;
पूर्ण

/* add a cleanup function by takahiro */
काष्ठा pool अणु
	काष्ठा pool *next;
	व्योम *mem;
पूर्ण;

अटल काष्ठा pool *pool_head;

अटल व्योम *my_दो_स्मृति(माप_प्रकार size)
अणु
	काष्ठा pool *p;

	p = सुस्मृति(1, माप(काष्ठा pool));
	अगर (!p)
		वापस शून्य;

	p->mem = सुस्मृति(1, size);
	अगर (!p->mem) अणु
		मुक्त(p);
		वापस शून्य;
	पूर्ण

	p->next = pool_head;
	pool_head = p;

	वापस p->mem;
पूर्ण

व्योम names_मुक्त(व्योम)
अणु
	काष्ठा pool *pool;

	अगर (!pool_head)
		वापस;

	क्रम (pool = pool_head; pool != शून्य; ) अणु
		काष्ठा pool *पंचांगp;

		अगर (pool->mem)
			मुक्त(pool->mem);

		पंचांगp = pool;
		pool = pool->next;
		मुक्त(पंचांगp);
	पूर्ण
पूर्ण

अटल पूर्णांक new_venकरोr(स्थिर अक्षर *name, u_पूर्णांक16_t venकरोrid)
अणु
	काष्ठा venकरोr *v;
	अचिन्हित पूर्णांक h = hashnum(venकरोrid);

	v = venकरोrs[h];
	क्रम (; v; v = v->next)
		अगर (v->venकरोrid == venकरोrid)
			वापस -1;
	v = my_दो_स्मृति(माप(काष्ठा venकरोr) + म_माप(name));
	अगर (!v)
		वापस -1;
	म_नकल(v->name, name);
	v->venकरोrid = venकरोrid;
	v->next = venकरोrs[h];
	venकरोrs[h] = v;
	वापस 0;
पूर्ण

अटल पूर्णांक new_product(स्थिर अक्षर *name, u_पूर्णांक16_t venकरोrid,
		       u_पूर्णांक16_t productid)
अणु
	काष्ठा product *p;
	अचिन्हित पूर्णांक h = hashnum((venकरोrid << 16) | productid);

	p = products[h];
	क्रम (; p; p = p->next)
		अगर (p->venकरोrid == venकरोrid && p->productid == productid)
			वापस -1;
	p = my_दो_स्मृति(माप(काष्ठा product) + म_माप(name));
	अगर (!p)
		वापस -1;
	म_नकल(p->name, name);
	p->venकरोrid = venकरोrid;
	p->productid = productid;
	p->next = products[h];
	products[h] = p;
	वापस 0;
पूर्ण

अटल पूर्णांक new_class(स्थिर अक्षर *name, u_पूर्णांक8_t classid)
अणु
	काष्ठा class *c;
	अचिन्हित पूर्णांक h = hashnum(classid);

	c = classes[h];
	क्रम (; c; c = c->next)
		अगर (c->classid == classid)
			वापस -1;
	c = my_दो_स्मृति(माप(काष्ठा class) + म_माप(name));
	अगर (!c)
		वापस -1;
	म_नकल(c->name, name);
	c->classid = classid;
	c->next = classes[h];
	classes[h] = c;
	वापस 0;
पूर्ण

अटल पूर्णांक new_subclass(स्थिर अक्षर *name, u_पूर्णांक8_t classid, u_पूर्णांक8_t subclassid)
अणु
	काष्ठा subclass *s;
	अचिन्हित पूर्णांक h = hashnum((classid << 8) | subclassid);

	s = subclasses[h];
	क्रम (; s; s = s->next)
		अगर (s->classid == classid && s->subclassid == subclassid)
			वापस -1;
	s = my_दो_स्मृति(माप(काष्ठा subclass) + म_माप(name));
	अगर (!s)
		वापस -1;
	म_नकल(s->name, name);
	s->classid = classid;
	s->subclassid = subclassid;
	s->next = subclasses[h];
	subclasses[h] = s;
	वापस 0;
पूर्ण

अटल पूर्णांक new_protocol(स्थिर अक्षर *name, u_पूर्णांक8_t classid, u_पूर्णांक8_t subclassid,
			u_पूर्णांक8_t protocolid)
अणु
	काष्ठा protocol *p;
	अचिन्हित पूर्णांक h = hashnum((classid << 16) | (subclassid << 8)
				 | protocolid);

	p = protocols[h];
	क्रम (; p; p = p->next)
		अगर (p->classid == classid && p->subclassid == subclassid
		    && p->protocolid == protocolid)
			वापस -1;
	p = my_दो_स्मृति(माप(काष्ठा protocol) + म_माप(name));
	अगर (!p)
		वापस -1;
	म_नकल(p->name, name);
	p->classid = classid;
	p->subclassid = subclassid;
	p->protocolid = protocolid;
	p->next = protocols[h];
	protocols[h] = p;
	वापस 0;
पूर्ण

अटल व्योम parse(खाता *f)
अणु
	अक्षर buf[512], *cp;
	अचिन्हित पूर्णांक linectr = 0;
	पूर्णांक lastvenकरोr = -1;
	पूर्णांक lastclass = -1;
	पूर्णांक lastsubclass = -1;
	पूर्णांक lasthut = -1;
	पूर्णांक lastlang = -1;
	अचिन्हित पूर्णांक u;

	जबतक (ख_माला_लो(buf, माप(buf), f)) अणु
		linectr++;
		/* हटाओ line ends */
		cp = म_अक्षर(buf, '\r');
		अगर (cp)
			*cp = 0;
		cp = म_अक्षर(buf, '\n');
		अगर (cp)
			*cp = 0;
		अगर (buf[0] == '#' || !buf[0])
			जारी;
		cp = buf;
		अगर (buf[0] == 'P' && buf[1] == 'H' && buf[2] == 'Y' &&
		    buf[3] == 'S' && buf[4] == 'D' &&
		    buf[5] == 'E' && buf[6] == 'S' && /*है_खाली(buf[7])*/
		    buf[7] == ' ') अणु
			जारी;
		पूर्ण
		अगर (buf[0] == 'P' && buf[1] == 'H' &&
		    buf[2] == 'Y' && /*isspace(buf[3])*/ buf[3] == ' ') अणु
			जारी;
		पूर्ण
		अगर (buf[0] == 'B' && buf[1] == 'I' && buf[2] == 'A' &&
		    buf[3] == 'S' && /*isspace(buf[4])*/ buf[4] == ' ') अणु
			जारी;
		पूर्ण
		अगर (buf[0] == 'L' && /*isspace(buf[1])*/ buf[1] == ' ') अणु
			lasthut = lastclass = lastvenकरोr = lastsubclass = -1;
			/*
			 * set 1 as pseuकरो-id to indicate that the parser is
			 * in a `L' section.
			 */
			lastlang = 1;
			जारी;
		पूर्ण
		अगर (buf[0] == 'C' && /*isspace(buf[1])*/ buf[1] == ' ') अणु
			/* class spec */
			cp = buf+2;
			जबतक (है_खाली(*cp))
				cp++;
			अगर (!है_षष्ठादशक(*cp)) अणु
				err("Invalid class spec at line %u", linectr);
				जारी;
			पूर्ण
			u = म_से_अदीर्घ(cp, &cp, 16);
			जबतक (है_खाली(*cp))
				cp++;
			अगर (!*cp) अणु
				err("Invalid class spec at line %u", linectr);
				जारी;
			पूर्ण
			अगर (new_class(cp, u))
				err("Duplicate class spec at line %u class %04x %s",
				    linectr, u, cp);
			dbg("line %5u class %02x %s", linectr, u, cp);
			lasthut = lastlang = lastvenकरोr = lastsubclass = -1;
			lastclass = u;
			जारी;
		पूर्ण
		अगर (buf[0] == 'A' && buf[1] == 'T' && है_खाली(buf[2])) अणु
			/* audio terminal type spec */
			जारी;
		पूर्ण
		अगर (buf[0] == 'H' && buf[1] == 'C' && buf[2] == 'C'
		    && है_खाली(buf[3])) अणु
			/* HID Descriptor bCountryCode */
			जारी;
		पूर्ण
		अगर (है_षष्ठादशक(*cp)) अणु
			/* venकरोr */
			u = म_से_अदीर्घ(cp, &cp, 16);
			जबतक (है_खाली(*cp))
				cp++;
			अगर (!*cp) अणु
				err("Invalid vendor spec at line %u", linectr);
				जारी;
			पूर्ण
			अगर (new_venकरोr(cp, u))
				err("Duplicate vendor spec at line %u vendor %04x %s",
				    linectr, u, cp);
			dbg("line %5u vendor %04x %s", linectr, u, cp);
			lastvenकरोr = u;
			lasthut = lastlang = lastclass = lastsubclass = -1;
			जारी;
		पूर्ण
		अगर (buf[0] == '\t' && है_षष्ठादशक(buf[1])) अणु
			/* product or subclass spec */
			u = म_से_अदीर्घ(buf+1, &cp, 16);
			जबतक (है_खाली(*cp))
				cp++;
			अगर (!*cp) अणु
				err("Invalid product/subclass spec at line %u",
				    linectr);
				जारी;
			पूर्ण
			अगर (lastvenकरोr != -1) अणु
				अगर (new_product(cp, lastvenकरोr, u))
					err("Duplicate product spec at line %u product %04x:%04x %s",
					    linectr, lastvenकरोr, u, cp);
				dbg("line %5u product %04x:%04x %s", linectr,
				    lastvenकरोr, u, cp);
				जारी;
			पूर्ण
			अगर (lastclass != -1) अणु
				अगर (new_subclass(cp, lastclass, u))
					err("Duplicate subclass spec at line %u class %02x:%02x %s",
					    linectr, lastclass, u, cp);
				dbg("line %5u subclass %02x:%02x %s", linectr,
				    lastclass, u, cp);
				lastsubclass = u;
				जारी;
			पूर्ण
			अगर (lasthut != -1) अणु
				/* करो not store hut */
				जारी;
			पूर्ण
			अगर (lastlang != -1) अणु
				/* करो not store langid */
				जारी;
			पूर्ण
			err("Product/Subclass spec without prior Vendor/Class spec at line %u",
			    linectr);
			जारी;
		पूर्ण
		अगर (buf[0] == '\t' && buf[1] == '\t' && है_षष्ठादशक(buf[2])) अणु
			/* protocol spec */
			u = म_से_अदीर्घ(buf+2, &cp, 16);
			जबतक (है_खाली(*cp))
				cp++;
			अगर (!*cp) अणु
				err("Invalid protocol spec at line %u",
				    linectr);
				जारी;
			पूर्ण
			अगर (lastclass != -1 && lastsubclass != -1) अणु
				अगर (new_protocol(cp, lastclass, lastsubclass,
						 u))
					err("Duplicate protocol spec at line %u class %02x:%02x:%02x %s",
					    linectr, lastclass, lastsubclass,
					    u, cp);
				dbg("line %5u protocol %02x:%02x:%02x %s",
				    linectr, lastclass, lastsubclass, u, cp);
				जारी;
			पूर्ण
			err("Protocol spec without prior Class and Subclass spec at line %u",
			    linectr);
			जारी;
		पूर्ण
		अगर (buf[0] == 'H' && buf[1] == 'I' &&
		    buf[2] == 'D' && /*isspace(buf[3])*/ buf[3] == ' ') अणु
			जारी;
		पूर्ण
		अगर (buf[0] == 'H' && buf[1] == 'U' &&
		    buf[2] == 'T' && /*isspace(buf[3])*/ buf[3] == ' ') अणु
			lastlang = lastclass = lastvenकरोr = lastsubclass = -1;
			/*
			 * set 1 as pseuकरो-id to indicate that the parser is
			 * in a `HUT' section.
			 */
			lasthut = 1;
			जारी;
		पूर्ण
		अगर (buf[0] == 'R' && buf[1] == ' ')
			जारी;

		अगर (buf[0] == 'V' && buf[1] == 'T')
			जारी;

		err("Unknown line at line %u", linectr);
	पूर्ण
पूर्ण


पूर्णांक names_init(अक्षर *n)
अणु
	खाता *f;

	f = ख_खोलो(n, "r");
	अगर (!f)
		वापस त्रुटि_सं;

	parse(f);
	ख_बंद(f);
	वापस 0;
पूर्ण
