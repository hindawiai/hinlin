<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of s390 diagnose codes
 *
 * Copyright IBM Corp. 2007
 * Author(s): Michael Holzheu <holzheu@de.ibm.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/trace/diag.h>
#समावेश <यंत्र/sections.h>

काष्ठा diag_stat अणु
	अचिन्हित पूर्णांक counter[NR_DIAG_STAT];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा diag_stat, diag_stat);

काष्ठा diag_desc अणु
	पूर्णांक code;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा diag_desc diag_map[NR_DIAG_STAT] = अणु
	[DIAG_STAT_X008] = अणु .code = 0x008, .name = "Console Function" पूर्ण,
	[DIAG_STAT_X00C] = अणु .code = 0x00c, .name = "Pseudo Timer" पूर्ण,
	[DIAG_STAT_X010] = अणु .code = 0x010, .name = "Release Pages" पूर्ण,
	[DIAG_STAT_X014] = अणु .code = 0x014, .name = "Spool File Services" पूर्ण,
	[DIAG_STAT_X044] = अणु .code = 0x044, .name = "Voluntary Timeslice End" पूर्ण,
	[DIAG_STAT_X064] = अणु .code = 0x064, .name = "NSS Manipulation" पूर्ण,
	[DIAG_STAT_X09C] = अणु .code = 0x09c, .name = "Relinquish Timeslice" पूर्ण,
	[DIAG_STAT_X0DC] = अणु .code = 0x0dc, .name = "Appldata Control" पूर्ण,
	[DIAG_STAT_X204] = अणु .code = 0x204, .name = "Logical-CPU Utilization" पूर्ण,
	[DIAG_STAT_X210] = अणु .code = 0x210, .name = "Device Information" पूर्ण,
	[DIAG_STAT_X224] = अणु .code = 0x224, .name = "EBCDIC-Name Table" पूर्ण,
	[DIAG_STAT_X250] = अणु .code = 0x250, .name = "Block I/O" पूर्ण,
	[DIAG_STAT_X258] = अणु .code = 0x258, .name = "Page-Reference Services" पूर्ण,
	[DIAG_STAT_X26C] = अणु .code = 0x26c, .name = "Certain System Information" पूर्ण,
	[DIAG_STAT_X288] = अणु .code = 0x288, .name = "Time Bomb" पूर्ण,
	[DIAG_STAT_X2C4] = अणु .code = 0x2c4, .name = "FTP Services" पूर्ण,
	[DIAG_STAT_X2FC] = अणु .code = 0x2fc, .name = "Guest Performance Data" पूर्ण,
	[DIAG_STAT_X304] = अणु .code = 0x304, .name = "Partition-Resource Service" पूर्ण,
	[DIAG_STAT_X308] = अणु .code = 0x308, .name = "List-Directed IPL" पूर्ण,
	[DIAG_STAT_X318] = अणु .code = 0x318, .name = "CP Name and Version Codes" पूर्ण,
	[DIAG_STAT_X500] = अणु .code = 0x500, .name = "Virtio Service" पूर्ण,
पूर्ण;

काष्ठा diag_ops __bootdata_preserved(diag_dma_ops);
काष्ठा diag210 *__bootdata_preserved(__diag210_पंचांगp_dma);

अटल पूर्णांक show_diag_stat(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा diag_stat *stat;
	अचिन्हित दीर्घ n = (अचिन्हित दीर्घ) v - 1;
	पूर्णांक cpu, prec, पंचांगp;

	get_online_cpus();
	अगर (n == 0) अणु
		seq_माला_दो(m, "         ");

		क्रम_each_online_cpu(cpu) अणु
			prec = 10;
			क्रम (पंचांगp = 10; cpu >= पंचांगp; पंचांगp *= 10)
				prec--;
			seq_म_लिखो(m, "%*s%d", prec, "CPU", cpu);
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण अन्यथा अगर (n <= NR_DIAG_STAT) अणु
		seq_म_लिखो(m, "diag %03x:", diag_map[n-1].code);
		क्रम_each_online_cpu(cpu) अणु
			stat = &per_cpu(diag_stat, cpu);
			seq_म_लिखो(m, " %10u", stat->counter[n-1]);
		पूर्ण
		seq_म_लिखो(m, "    %s\n", diag_map[n-1].name);
	पूर्ण
	put_online_cpus();
	वापस 0;
पूर्ण

अटल व्योम *show_diag_stat_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस *pos <= NR_DIAG_STAT ? (व्योम *)((अचिन्हित दीर्घ) *pos + 1) : शून्य;
पूर्ण

अटल व्योम *show_diag_stat_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस show_diag_stat_start(m, pos);
पूर्ण

अटल व्योम show_diag_stat_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations show_diag_stat_sops = अणु
	.start	= show_diag_stat_start,
	.next	= show_diag_stat_next,
	.stop	= show_diag_stat_stop,
	.show	= show_diag_stat,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(show_diag_stat);

अटल पूर्णांक __init show_diag_stat_init(व्योम)
अणु
	debugfs_create_file("diag_stat", 0400, शून्य, शून्य,
			    &show_diag_stat_fops);
	वापस 0;
पूर्ण

device_initcall(show_diag_stat_init);

व्योम diag_stat_inc(क्रमागत diag_stat_क्रमागत nr)
अणु
	this_cpu_inc(diag_stat.counter[nr]);
	trace_s390_diagnose(diag_map[nr].code);
पूर्ण
EXPORT_SYMBOL(diag_stat_inc);

व्योम notrace diag_stat_inc_norecursion(क्रमागत diag_stat_क्रमागत nr)
अणु
	this_cpu_inc(diag_stat.counter[nr]);
	trace_s390_diagnose_norecursion(diag_map[nr].code);
पूर्ण
EXPORT_SYMBOL(diag_stat_inc_norecursion);

/*
 * Diagnose 14: Input spool file manipulation
 */
पूर्णांक diag14(अचिन्हित दीर्घ rx, अचिन्हित दीर्घ ry1, अचिन्हित दीर्घ subcode)
अणु
	diag_stat_inc(DIAG_STAT_X014);
	वापस diag_dma_ops.diag14(rx, ry1, subcode);
पूर्ण
EXPORT_SYMBOL(diag14);

अटल अंतरभूत पूर्णांक __diag204(अचिन्हित दीर्घ *subcode, अचिन्हित दीर्घ size, व्योम *addr)
अणु
	रेजिस्टर अचिन्हित दीर्घ _subcode यंत्र("0") = *subcode;
	रेजिस्टर अचिन्हित दीर्घ _size यंत्र("1") = size;

	यंत्र अस्थिर(
		"	diag	%2,%0,0x204\n"
		"0:	nopr	%%r7\n"
		EX_TABLE(0b,0b)
		: "+d" (_subcode), "+d" (_size) : "d" (addr) : "memory");
	*subcode = _subcode;
	वापस _size;
पूर्ण

पूर्णांक diag204(अचिन्हित दीर्घ subcode, अचिन्हित दीर्घ size, व्योम *addr)
अणु
	diag_stat_inc(DIAG_STAT_X204);
	size = __diag204(&subcode, size, addr);
	अगर (subcode)
		वापस -1;
	वापस size;
पूर्ण
EXPORT_SYMBOL(diag204);

/*
 * Diagnose 210: Get inक्रमmation about a भव device
 */
पूर्णांक diag210(काष्ठा diag210 *addr)
अणु
	अटल DEFINE_SPINLOCK(diag210_lock);
	अचिन्हित दीर्घ flags;
	पूर्णांक ccode;

	spin_lock_irqsave(&diag210_lock, flags);
	*__diag210_पंचांगp_dma = *addr;

	diag_stat_inc(DIAG_STAT_X210);
	ccode = diag_dma_ops.diag210(__diag210_पंचांगp_dma);

	*addr = *__diag210_पंचांगp_dma;
	spin_unlock_irqrestore(&diag210_lock, flags);

	वापस ccode;
पूर्ण
EXPORT_SYMBOL(diag210);

पूर्णांक diag224(व्योम *ptr)
अणु
	पूर्णांक rc = -EOPNOTSUPP;

	diag_stat_inc(DIAG_STAT_X224);
	यंत्र अस्थिर(
		"	diag	%1,%2,0x224\n"
		"0:	lhi	%0,0x0\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "+d" (rc) :"d" (0), "d" (ptr) : "memory");
	वापस rc;
पूर्ण
EXPORT_SYMBOL(diag224);

/*
 * Diagnose 26C: Access Certain System Inक्रमmation
 */
पूर्णांक diag26c(व्योम *req, व्योम *resp, क्रमागत diag26c_sc subcode)
अणु
	diag_stat_inc(DIAG_STAT_X26C);
	वापस diag_dma_ops.diag26c(req, resp, subcode);
पूर्ण
EXPORT_SYMBOL(diag26c);
