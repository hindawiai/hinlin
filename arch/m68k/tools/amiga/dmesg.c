<शैली गुरु>
/*
 *  linux/arch/m68k/tools/amiga/dmesg.c -- Retrieve the kernel messages stored
 *					   in Chip RAM with the kernel command
 *					   line option `debug=mem'.
 *
 *  तऊ Copyright 1996 by Geert Uytterhoeven <geert@linux-m68k.org>
 *
 *
 *  Usage:
 *
 *	dmesg
 *	dmesg <CHIPMEM_END>
 *
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of the Linux
 *  distribution क्रम more details.
 */


#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>


#घोषणा CHIPMEM_START	0x00000000
#घोषणा CHIPMEM_END	0x00200000	/* overridden by argv[1] */

#घोषणा SAVEKMSG_MAGIC1	0x53415645	/* 'SAVE' */
#घोषणा SAVEKMSG_MAGIC2	0x4B4D5347	/* 'KMSG' */

काष्ठा savekmsg अणु
    u_दीर्घ magic1;	/* SAVEKMSG_MAGIC1 */
    u_दीर्घ magic2;	/* SAVEKMSG_MAGIC2 */
    u_दीर्घ magicptr;	/* address of magic1 */
    u_दीर्घ size;
    अक्षर data[];
पूर्ण;


पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
    u_दीर्घ start = CHIPMEM_START, end = CHIPMEM_END, p;
    पूर्णांक found = 0;
    काष्ठा savekmsg *m = शून्य;

    अगर (argc >= 2)
	end = म_से_अदीर्घ(argv[1], शून्य, 0);
    म_लिखो("Searching for SAVEKMSG magic...\n");
    क्रम (p = start; p <= end-माप(काष्ठा savekmsg); p += 4) अणु
	m = (काष्ठा savekmsg *)p;
	अगर ((m->magic1 == SAVEKMSG_MAGIC1) && (m->magic2 == SAVEKMSG_MAGIC2) &&
	    (m->magicptr == p)) अणु
	    found = 1;
	    अवरोध;
	पूर्ण
    पूर्ण
    अगर (!found)
	म_लिखो("Not found\n");
    अन्यथा अणु
	म_लिखो("Found %ld bytes at 0x%08lx\n", m->size, (u_दीर्घ)&m->data);
	माला_दो(">>>>>>>>>>>>>>>>>>>>");
	ख_साफ(मानक_निकास);
	ग_लिखो(1, &m->data, m->size);
	ख_साफ(मानक_निकास);
	माला_दो("<<<<<<<<<<<<<<<<<<<<");
    पूर्ण
    वापस(0);
पूर्ण
