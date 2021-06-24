<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Task I/O accounting operations
 */
#अगर_अघोषित __TASK_IO_ACCOUNTING_OPS_INCLUDED
#घोषणा __TASK_IO_ACCOUNTING_OPS_INCLUDED

#समावेश <linux/sched.h>

#अगर_घोषित CONFIG_TASK_IO_ACCOUNTING
अटल अंतरभूत व्योम task_io_account_पढ़ो(माप_प्रकार bytes)
अणु
	current->ioac.पढ़ो_bytes += bytes;
पूर्ण

/*
 * We approximate number of blocks, because we account bytes only.
 * A 'block' is 512 bytes
 */
अटल अंतरभूत अचिन्हित दीर्घ task_io_get_inblock(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस p->ioac.पढ़ो_bytes >> 9;
पूर्ण

अटल अंतरभूत व्योम task_io_account_ग_लिखो(माप_प्रकार bytes)
अणु
	current->ioac.ग_लिखो_bytes += bytes;
पूर्ण

/*
 * We approximate number of blocks, because we account bytes only.
 * A 'block' is 512 bytes
 */
अटल अंतरभूत अचिन्हित दीर्घ task_io_get_oublock(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस p->ioac.ग_लिखो_bytes >> 9;
पूर्ण

अटल अंतरभूत व्योम task_io_account_cancelled_ग_लिखो(माप_प्रकार bytes)
अणु
	current->ioac.cancelled_ग_लिखो_bytes += bytes;
पूर्ण

अटल अंतरभूत व्योम task_io_accounting_init(काष्ठा task_io_accounting *ioac)
अणु
	स_रखो(ioac, 0, माप(*ioac));
पूर्ण

अटल अंतरभूत व्योम task_blk_io_accounting_add(काष्ठा task_io_accounting *dst,
						काष्ठा task_io_accounting *src)
अणु
	dst->पढ़ो_bytes += src->पढ़ो_bytes;
	dst->ग_लिखो_bytes += src->ग_लिखो_bytes;
	dst->cancelled_ग_लिखो_bytes += src->cancelled_ग_लिखो_bytes;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम task_io_account_पढ़ो(माप_प्रकार bytes)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ task_io_get_inblock(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम task_io_account_ग_लिखो(माप_प्रकार bytes)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ task_io_get_oublock(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम task_io_account_cancelled_ग_लिखो(माप_प्रकार bytes)
अणु
पूर्ण

अटल अंतरभूत व्योम task_io_accounting_init(काष्ठा task_io_accounting *ioac)
अणु
पूर्ण

अटल अंतरभूत व्योम task_blk_io_accounting_add(काष्ठा task_io_accounting *dst,
						काष्ठा task_io_accounting *src)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_TASK_IO_ACCOUNTING */

#अगर_घोषित CONFIG_TASK_XACCT
अटल अंतरभूत व्योम task_chr_io_accounting_add(काष्ठा task_io_accounting *dst,
						काष्ठा task_io_accounting *src)
अणु
	dst->rअक्षर += src->rअक्षर;
	dst->wअक्षर += src->wअक्षर;
	dst->syscr += src->syscr;
	dst->syscw += src->syscw;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम task_chr_io_accounting_add(काष्ठा task_io_accounting *dst,
						काष्ठा task_io_accounting *src)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_TASK_XACCT */

अटल अंतरभूत व्योम task_io_accounting_add(काष्ठा task_io_accounting *dst,
						काष्ठा task_io_accounting *src)
अणु
	task_chr_io_accounting_add(dst, src);
	task_blk_io_accounting_add(dst, src);
पूर्ण
#पूर्ण_अगर /* __TASK_IO_ACCOUNTING_OPS_INCLUDED */
