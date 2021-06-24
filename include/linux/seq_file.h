<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SEQ_खाता_H
#घोषणा _LINUX_SEQ_खाता_H

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/bug.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/fs.h>
#समावेश <linux/cred.h>

काष्ठा seq_operations;

काष्ठा seq_file अणु
	अक्षर *buf;
	माप_प्रकार size;
	माप_प्रकार from;
	माप_प्रकार count;
	माप_प्रकार pad_until;
	loff_t index;
	loff_t पढ़ो_pos;
	काष्ठा mutex lock;
	स्थिर काष्ठा seq_operations *op;
	पूर्णांक poll_event;
	स्थिर काष्ठा file *file;
	व्योम *निजी;
पूर्ण;

काष्ठा seq_operations अणु
	व्योम * (*start) (काष्ठा seq_file *m, loff_t *pos);
	व्योम (*stop) (काष्ठा seq_file *m, व्योम *v);
	व्योम * (*next) (काष्ठा seq_file *m, व्योम *v, loff_t *pos);
	पूर्णांक (*show) (काष्ठा seq_file *m, व्योम *v);
पूर्ण;

#घोषणा SEQ_SKIP 1

/**
 * seq_has_overflowed - check अगर the buffer has overflowed
 * @m: the seq_file handle
 *
 * seq_files have a buffer which may overflow. When this happens a larger
 * buffer is पुनः_स्मृतिated and all the data will be prपूर्णांकed again.
 * The overflow state is true when m->count == m->size.
 *
 * Returns true अगर the buffer received more than it can hold.
 */
अटल अंतरभूत bool seq_has_overflowed(काष्ठा seq_file *m)
अणु
	वापस m->count == m->size;
पूर्ण

/**
 * seq_get_buf - get buffer to ग_लिखो arbitrary data to
 * @m: the seq_file handle
 * @bufp: the beginning of the buffer is stored here
 *
 * Return the number of bytes available in the buffer, or zero अगर
 * there's no space.
 */
अटल अंतरभूत माप_प्रकार seq_get_buf(काष्ठा seq_file *m, अक्षर **bufp)
अणु
	BUG_ON(m->count > m->size);
	अगर (m->count < m->size)
		*bufp = m->buf + m->count;
	अन्यथा
		*bufp = शून्य;

	वापस m->size - m->count;
पूर्ण

/**
 * seq_commit - commit data to the buffer
 * @m: the seq_file handle
 * @num: the number of bytes to commit
 *
 * Commit @num bytes of data written to a buffer previously acquired
 * by seq_buf_get.  To संकेत an error condition, or that the data
 * didn't fit in the available space, pass a negative @num value.
 */
अटल अंतरभूत व्योम seq_commit(काष्ठा seq_file *m, पूर्णांक num)
अणु
	अगर (num < 0) अणु
		m->count = m->size;
	पूर्ण अन्यथा अणु
		BUG_ON(m->count + num > m->size);
		m->count += num;
	पूर्ण
पूर्ण

/**
 * seq_setwidth - set padding width
 * @m: the seq_file handle
 * @size: the max number of bytes to pad.
 *
 * Call seq_setwidth() क्रम setting max width, then call seq_म_लिखो() etc. and
 * finally call seq_pad() to pad the reमुख्यing bytes.
 */
अटल अंतरभूत व्योम seq_setwidth(काष्ठा seq_file *m, माप_प्रकार size)
अणु
	m->pad_until = m->count + size;
पूर्ण
व्योम seq_pad(काष्ठा seq_file *m, अक्षर c);

अक्षर *mangle_path(अक्षर *s, स्थिर अक्षर *p, स्थिर अक्षर *esc);
पूर्णांक seq_खोलो(काष्ठा file *, स्थिर काष्ठा seq_operations *);
sमाप_प्रकार seq_पढ़ो(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
sमाप_प्रकार seq_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter);
loff_t seq_lseek(काष्ठा file *, loff_t, पूर्णांक);
पूर्णांक seq_release(काष्ठा inode *, काष्ठा file *);
पूर्णांक seq_ग_लिखो(काष्ठा seq_file *seq, स्थिर व्योम *data, माप_प्रकार len);

__म_लिखो(2, 0)
व्योम seq_भ_लिखो(काष्ठा seq_file *m, स्थिर अक्षर *fmt, बहु_सूची args);
__म_लिखो(2, 3)
व्योम seq_म_लिखो(काष्ठा seq_file *m, स्थिर अक्षर *fmt, ...);
व्योम seq_अ_दो(काष्ठा seq_file *m, अक्षर c);
व्योम seq_माला_दो(काष्ठा seq_file *m, स्थिर अक्षर *s);
व्योम seq_put_decimal_ull_width(काष्ठा seq_file *m, स्थिर अक्षर *delimiter,
			       अचिन्हित दीर्घ दीर्घ num, अचिन्हित पूर्णांक width);
व्योम seq_put_decimal_ull(काष्ठा seq_file *m, स्थिर अक्षर *delimiter,
			 अचिन्हित दीर्घ दीर्घ num);
व्योम seq_put_decimal_ll(काष्ठा seq_file *m, स्थिर अक्षर *delimiter, दीर्घ दीर्घ num);
व्योम seq_put_hex_ll(काष्ठा seq_file *m, स्थिर अक्षर *delimiter,
		    अचिन्हित दीर्घ दीर्घ v, अचिन्हित पूर्णांक width);

व्योम seq_escape(काष्ठा seq_file *m, स्थिर अक्षर *s, स्थिर अक्षर *esc);
व्योम seq_escape_mem_ascii(काष्ठा seq_file *m, स्थिर अक्षर *src, माप_प्रकार isz);

व्योम seq_hex_dump(काष्ठा seq_file *m, स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
		  पूर्णांक rowsize, पूर्णांक groupsize, स्थिर व्योम *buf, माप_प्रकार len,
		  bool ascii);

पूर्णांक seq_path(काष्ठा seq_file *, स्थिर काष्ठा path *, स्थिर अक्षर *);
पूर्णांक seq_file_path(काष्ठा seq_file *, काष्ठा file *, स्थिर अक्षर *);
पूर्णांक seq_dentry(काष्ठा seq_file *, काष्ठा dentry *, स्थिर अक्षर *);
पूर्णांक seq_path_root(काष्ठा seq_file *m, स्थिर काष्ठा path *path,
		  स्थिर काष्ठा path *root, स्थिर अक्षर *esc);

पूर्णांक single_खोलो(काष्ठा file *, पूर्णांक (*)(काष्ठा seq_file *, व्योम *), व्योम *);
पूर्णांक single_खोलो_size(काष्ठा file *, पूर्णांक (*)(काष्ठा seq_file *, व्योम *), व्योम *, माप_प्रकार);
पूर्णांक single_release(काष्ठा inode *, काष्ठा file *);
व्योम *__seq_खोलो_निजी(काष्ठा file *, स्थिर काष्ठा seq_operations *, पूर्णांक);
पूर्णांक seq_खोलो_निजी(काष्ठा file *, स्थिर काष्ठा seq_operations *, पूर्णांक);
पूर्णांक seq_release_निजी(काष्ठा inode *, काष्ठा file *);

#अगर_घोषित CONFIG_BINARY_PRINTF
व्योम seq_bम_लिखो(काष्ठा seq_file *m, स्थिर अक्षर *f, स्थिर u32 *binary);
#पूर्ण_अगर

#घोषणा DEFINE_SEQ_ATTRIBUTE(__name)					\
अटल पूर्णांक __name ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	पूर्णांक ret = seq_खोलो(file, &__name ## _sops);			\
	अगर (!ret && inode->i_निजी) अणु					\
		काष्ठा seq_file *seq_f = file->निजी_data;		\
		seq_f->निजी = inode->i_निजी;			\
	पूर्ण								\
	वापस ret;							\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations __name ## _fops = अणु			\
	.owner		= THIS_MODULE,					\
	.खोलो		= __name ## _खोलो,				\
	.पढ़ो		= seq_पढ़ो,					\
	.llseek		= seq_lseek,					\
	.release	= seq_release,					\
पूर्ण

#घोषणा DEFINE_SHOW_ATTRIBUTE(__name)					\
अटल पूर्णांक __name ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	वापस single_खोलो(file, __name ## _show, inode->i_निजी);	\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations __name ## _fops = अणु			\
	.owner		= THIS_MODULE,					\
	.खोलो		= __name ## _खोलो,				\
	.पढ़ो		= seq_पढ़ो,					\
	.llseek		= seq_lseek,					\
	.release	= single_release,				\
पूर्ण

#घोषणा DEFINE_PROC_SHOW_ATTRIBUTE(__name)				\
अटल पूर्णांक __name ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	वापस single_खोलो(file, __name ## _show, inode->i_निजी);	\
पूर्ण									\
									\
अटल स्थिर काष्ठा proc_ops __name ## _proc_ops = अणु			\
	.proc_खोलो	= __name ## _खोलो,				\
	.proc_पढ़ो	= seq_पढ़ो,					\
	.proc_lseek	= seq_lseek,					\
	.proc_release	= single_release,				\
पूर्ण

अटल अंतरभूत काष्ठा user_namespace *seq_user_ns(काष्ठा seq_file *seq)
अणु
#अगर_घोषित CONFIG_USER_NS
	वापस seq->file->f_cred->user_ns;
#अन्यथा
	बाह्य काष्ठा user_namespace init_user_ns;
	वापस &init_user_ns;
#पूर्ण_अगर
पूर्ण

/**
 * seq_show_options - display mount options with appropriate escapes.
 * @m: the seq_file handle
 * @name: the mount option name
 * @value: the mount option name's value, can be शून्य
 */
अटल अंतरभूत व्योम seq_show_option(काष्ठा seq_file *m, स्थिर अक्षर *name,
				   स्थिर अक्षर *value)
अणु
	seq_अ_दो(m, ',');
	seq_escape(m, name, ",= \t\n\\");
	अगर (value) अणु
		seq_अ_दो(m, '=');
		seq_escape(m, value, ", \t\n\\");
	पूर्ण
पूर्ण

/**
 * seq_show_option_n - display mount options with appropriate escapes
 *		       where @value must be a specअगरic length.
 * @m: the seq_file handle
 * @name: the mount option name
 * @value: the mount option name's value, cannot be शून्य
 * @length: the length of @value to display
 *
 * This is a macro since this uses "length" to define the size of the
 * stack buffer.
 */
#घोषणा seq_show_option_n(m, name, value, length) अणु	\
	अक्षर val_buf[length + 1];			\
	म_नकलन(val_buf, value, length);		\
	val_buf[length] = '\0';				\
	seq_show_option(m, name, val_buf);		\
पूर्ण

#घोषणा SEQ_START_TOKEN ((व्योम *)1)
/*
 * Helpers क्रम iteration over list_head-s in seq_files
 */

बाह्य काष्ठा list_head *seq_list_start(काष्ठा list_head *head,
		loff_t pos);
बाह्य काष्ठा list_head *seq_list_start_head(काष्ठा list_head *head,
		loff_t pos);
बाह्य काष्ठा list_head *seq_list_next(व्योम *v, काष्ठा list_head *head,
		loff_t *ppos);

/*
 * Helpers क्रम iteration over hlist_head-s in seq_files
 */

बाह्य काष्ठा hlist_node *seq_hlist_start(काष्ठा hlist_head *head,
					  loff_t pos);
बाह्य काष्ठा hlist_node *seq_hlist_start_head(काष्ठा hlist_head *head,
					       loff_t pos);
बाह्य काष्ठा hlist_node *seq_hlist_next(व्योम *v, काष्ठा hlist_head *head,
					 loff_t *ppos);

बाह्य काष्ठा hlist_node *seq_hlist_start_rcu(काष्ठा hlist_head *head,
					      loff_t pos);
बाह्य काष्ठा hlist_node *seq_hlist_start_head_rcu(काष्ठा hlist_head *head,
						   loff_t pos);
बाह्य काष्ठा hlist_node *seq_hlist_next_rcu(व्योम *v,
						   काष्ठा hlist_head *head,
						   loff_t *ppos);

/* Helpers क्रम iterating over per-cpu hlist_head-s in seq_files */
बाह्य काष्ठा hlist_node *seq_hlist_start_percpu(काष्ठा hlist_head __percpu *head, पूर्णांक *cpu, loff_t pos);

बाह्य काष्ठा hlist_node *seq_hlist_next_percpu(व्योम *v, काष्ठा hlist_head __percpu *head, पूर्णांक *cpu, loff_t *pos);

व्योम seq_file_init(व्योम);
#पूर्ण_अगर
