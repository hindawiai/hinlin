<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IBM/3270 Driver
 *
 * Author(s):
 *   Original 3270 Code क्रम 2.4 written by Riअक्षरd Hitt (UTS Global)
 *   Rewritten क्रम 2.5 by Martin Schwidefsky <schwidefsky@de.ibm.com>
 *     Copyright IBM Corp. 2003, 2009
 */

#समावेश <यंत्र/idals.h>
#समावेश <यंत्र/ioctl.h>

/* ioctls क्रम fullscreen 3270 */
#घोषणा TUBICMD		_IO('3', 3)	/* set ccw command क्रम fs पढ़ोs. */
#घोषणा TUBOCMD		_IO('3', 4)	/* set ccw command क्रम fs ग_लिखोs. */
#घोषणा TUBGETI		_IO('3', 7)	/* get ccw command क्रम fs पढ़ोs. */
#घोषणा TUBGETO		_IO('3', 8)	/* get ccw command क्रम fs ग_लिखोs. */
#घोषणा TUBSETMOD	_IO('3',12)	/* FIXME: what करोes it करो ?*/
#घोषणा TUBGETMOD	_IO('3',13)	/* FIXME: what करोes it करो ?*/

/* Local Channel Commands */
#घोषणा TC_WRITE	0x01		/* Write */
#घोषणा TC_RDBUF	0x02		/* Read Buffer */
#घोषणा TC_EWRITE	0x05		/* Erase ग_लिखो */
#घोषणा TC_READMOD	0x06		/* Read modअगरied */
#घोषणा TC_EWRITEA	0x0d		/* Erase ग_लिखो alternate */
#घोषणा TC_WRITESF	0x11		/* Write काष्ठाured field */

/* Buffer Control Orders */
#घोषणा TO_SF		0x1d		/* Start field */
#घोषणा TO_SBA		0x11		/* Set buffer address */
#घोषणा TO_IC		0x13		/* Insert cursor */
#घोषणा TO_PT		0x05		/* Program tab */
#घोषणा TO_RA		0x3c		/* Repeat to address */
#घोषणा TO_SFE		0x29		/* Start field extended */
#घोषणा TO_EUA		0x12		/* Erase unरक्षित to address */
#घोषणा TO_MF		0x2c		/* Modअगरy field */
#घोषणा TO_SA		0x28		/* Set attribute */

/* Field Attribute Bytes */
#घोषणा TF_INPUT	0x40		/* Visible input */
#घोषणा TF_INPUTN	0x4c		/* Invisible input */
#घोषणा TF_INMDT	0xc1		/* Visible, Set-MDT */
#घोषणा TF_LOG		0x60

/* Character Attribute Bytes */
#घोषणा TAT_RESET	0x00
#घोषणा TAT_FIELD	0xc0
#घोषणा TAT_EXTHI	0x41
#घोषणा TAT_COLOR	0x42
#घोषणा TAT_CHARS	0x43
#घोषणा TAT_TRANS	0x46

/* Extended-Highlighting Bytes */
#घोषणा TAX_RESET	0x00
#घोषणा TAX_BLINK	0xf1
#घोषणा TAX_REVER	0xf2
#घोषणा TAX_UNDER	0xf4

/* Reset value */
#घोषणा TAR_RESET	0x00

/* Color values */
#घोषणा TAC_RESET	0x00
#घोषणा TAC_BLUE	0xf1
#घोषणा TAC_RED		0xf2
#घोषणा TAC_PINK	0xf3
#घोषणा TAC_GREEN	0xf4
#घोषणा TAC_TURQ	0xf5
#घोषणा TAC_YELLOW	0xf6
#घोषणा TAC_WHITE	0xf7
#घोषणा TAC_DEFAULT	0x00

/* Write Control Characters */
#घोषणा TW_NONE		0x40		/* No particular action */
#घोषणा TW_KR		0xc2		/* Keyboard restore */
#घोषणा TW_PLUSALARM	0x04		/* Add this bit क्रम alarm */

#घोषणा RAW3270_FIRSTMINOR	1	/* First minor number */
#घोषणा RAW3270_MAXDEVS		255	/* Max number of 3270 devices */

/* For TUBGETMOD and TUBSETMOD. Should include. */
काष्ठा raw3270_iocb अणु
	लघु model;
	लघु line_cnt;
	लघु col_cnt;
	लघु pf_cnt;
	लघु re_cnt;
	लघु map;
पूर्ण;

काष्ठा raw3270;
काष्ठा raw3270_view;
बाह्य काष्ठा class *class3270;

/* 3270 CCW request */
काष्ठा raw3270_request अणु
	काष्ठा list_head list;		/* list head क्रम request queueing. */
	काष्ठा raw3270_view *view;	/* view of this request */
	काष्ठा ccw1 ccw;		/* single ccw. */
	व्योम *buffer;			/* output buffer. */
	माप_प्रकार size;			/* size of output buffer. */
	पूर्णांक rescnt;			/* residual count from devstat. */
	पूर्णांक rc;				/* वापस code क्रम this request. */

	/* Callback क्रम delivering final status. */
	व्योम (*callback)(काष्ठा raw3270_request *, व्योम *);
	व्योम *callback_data;
पूर्ण;

काष्ठा raw3270_request *raw3270_request_alloc(माप_प्रकार size);
व्योम raw3270_request_मुक्त(काष्ठा raw3270_request *);
व्योम raw3270_request_reset(काष्ठा raw3270_request *);
व्योम raw3270_request_set_cmd(काष्ठा raw3270_request *, u8 cmd);
पूर्णांक  raw3270_request_add_data(काष्ठा raw3270_request *, व्योम *, माप_प्रकार);
व्योम raw3270_request_set_data(काष्ठा raw3270_request *, व्योम *, माप_प्रकार);
व्योम raw3270_request_set_idal(काष्ठा raw3270_request *, काष्ठा idal_buffer *);

अटल अंतरभूत पूर्णांक
raw3270_request_final(काष्ठा raw3270_request *rq)
अणु
	वापस list_empty(&rq->list);
पूर्ण

व्योम raw3270_buffer_address(काष्ठा raw3270 *, अक्षर *, अचिन्हित लघु);

/*
 * Functions of a 3270 view.
 */
काष्ठा raw3270_fn अणु
	पूर्णांक  (*activate)(काष्ठा raw3270_view *);
	व्योम (*deactivate)(काष्ठा raw3270_view *);
	व्योम (*पूर्णांकv)(काष्ठा raw3270_view *,
		     काष्ठा raw3270_request *, काष्ठा irb *);
	व्योम (*release)(काष्ठा raw3270_view *);
	व्योम (*मुक्त)(काष्ठा raw3270_view *);
	व्योम (*resize)(काष्ठा raw3270_view *, पूर्णांक, पूर्णांक, पूर्णांक);
पूर्ण;

/*
 * View काष्ठाure chaining. The raw3270_view काष्ठाure is meant to
 * be embedded at the start of the real view data काष्ठाure, e.g.:
 *   काष्ठा example अणु
 *     काष्ठा raw3270_view view;
 *     ...
 *   पूर्ण;
 */
काष्ठा raw3270_view अणु
	काष्ठा list_head list;
	spinlock_t lock;
#घोषणा RAW3270_VIEW_LOCK_IRQ	0
#घोषणा RAW3270_VIEW_LOCK_BH	1
	atomic_t ref_count;
	काष्ठा raw3270 *dev;
	काष्ठा raw3270_fn *fn;
	अचिन्हित पूर्णांक model;
	अचिन्हित पूर्णांक rows, cols;	/* # of rows & colums of the view */
	अचिन्हित अक्षर *ascebc;		/* ascii -> ebcdic table */
पूर्ण;

पूर्णांक raw3270_add_view(काष्ठा raw3270_view *, काष्ठा raw3270_fn *, पूर्णांक, पूर्णांक);
पूर्णांक raw3270_activate_view(काष्ठा raw3270_view *);
व्योम raw3270_del_view(काष्ठा raw3270_view *);
व्योम raw3270_deactivate_view(काष्ठा raw3270_view *);
काष्ठा raw3270_view *raw3270_find_view(काष्ठा raw3270_fn *, पूर्णांक);
पूर्णांक raw3270_start(काष्ठा raw3270_view *, काष्ठा raw3270_request *);
पूर्णांक raw3270_start_locked(काष्ठा raw3270_view *, काष्ठा raw3270_request *);
पूर्णांक raw3270_start_irq(काष्ठा raw3270_view *, काष्ठा raw3270_request *);
पूर्णांक raw3270_reset(काष्ठा raw3270_view *);
काष्ठा raw3270_view *raw3270_view(काष्ठा raw3270_view *);
पूर्णांक raw3270_view_active(काष्ठा raw3270_view *);

/* Reference count अंतरभूतr क्रम view काष्ठाures. */
अटल अंतरभूत व्योम
raw3270_get_view(काष्ठा raw3270_view *view)
अणु
	atomic_inc(&view->ref_count);
पूर्ण

बाह्य रुको_queue_head_t raw3270_रुको_queue;

अटल अंतरभूत व्योम
raw3270_put_view(काष्ठा raw3270_view *view)
अणु
	अगर (atomic_dec_वापस(&view->ref_count) == 0)
		wake_up(&raw3270_रुको_queue);
पूर्ण

काष्ठा raw3270 *raw3270_setup_console(व्योम);
व्योम raw3270_रुको_cons_dev(काष्ठा raw3270 *);

/* Notअगरier क्रम device addition/removal */
काष्ठा raw3270_notअगरier अणु
	काष्ठा list_head list;
	व्योम (*create)(पूर्णांक minor);
	व्योम (*destroy)(पूर्णांक minor);
पूर्ण;

पूर्णांक raw3270_रेजिस्टर_notअगरier(काष्ठा raw3270_notअगरier *);
व्योम raw3270_unरेजिस्टर_notअगरier(काष्ठा raw3270_notअगरier *);

/*
 * Little memory allocator क्रम string objects. 
 */
काष्ठा string
अणु
	काष्ठा list_head list;
	काष्ठा list_head update;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ len;
	अक्षर string[];
पूर्ण __attribute__ ((aligned(8)));

अटल अंतरभूत काष्ठा string *
alloc_string(काष्ठा list_head *मुक्त_list, अचिन्हित दीर्घ len)
अणु
	काष्ठा string *cs, *पंचांगp;
	अचिन्हित दीर्घ size;

	size = (len + 7L) & -8L;
	list_क्रम_each_entry(cs, मुक्त_list, list) अणु
		अगर (cs->size < size)
			जारी;
		अगर (cs->size > size + माप(काष्ठा string)) अणु
			अक्षर *endaddr = (अक्षर *) (cs + 1) + cs->size;
			पंचांगp = (काष्ठा string *) (endaddr - size) - 1;
			पंचांगp->size = size;
			cs->size -= size + माप(काष्ठा string);
			cs = पंचांगp;
		पूर्ण अन्यथा
			list_del(&cs->list);
		cs->len = len;
		INIT_LIST_HEAD(&cs->list);
		INIT_LIST_HEAD(&cs->update);
		वापस cs;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
मुक्त_string(काष्ठा list_head *मुक्त_list, काष्ठा string *cs)
अणु
	काष्ठा string *पंचांगp;
	काष्ठा list_head *p, *left;

	/* Find out the left neighbour in मुक्त memory list. */
	left = मुक्त_list;
	list_क्रम_each(p, मुक्त_list) अणु
		अगर (list_entry(p, काष्ठा string, list) > cs)
			अवरोध;
		left = p;
	पूर्ण
	/* Try to merge with right neighbour = next element from left. */
	अगर (left->next != मुक्त_list) अणु
		पंचांगp = list_entry(left->next, काष्ठा string, list);
		अगर ((अक्षर *) (cs + 1) + cs->size == (अक्षर *) पंचांगp) अणु
			list_del(&पंचांगp->list);
			cs->size += पंचांगp->size + माप(काष्ठा string);
		पूर्ण
	पूर्ण
	/* Try to merge with left neighbour. */
	अगर (left != मुक्त_list) अणु
		पंचांगp = list_entry(left, काष्ठा string, list);
		अगर ((अक्षर *) (पंचांगp + 1) + पंचांगp->size == (अक्षर *) cs) अणु
			पंचांगp->size += cs->size + माप(काष्ठा string);
			वापस पंचांगp->size;
		पूर्ण
	पूर्ण
	__list_add(&cs->list, left, left->next);
	वापस cs->size;
पूर्ण

अटल अंतरभूत व्योम
add_string_memory(काष्ठा list_head *मुक्त_list, व्योम *mem, अचिन्हित दीर्घ size)
अणु
	काष्ठा string *cs;

	cs = (काष्ठा string *) mem;
	cs->size = size - माप(काष्ठा string);
	मुक्त_string(मुक्त_list, cs);
पूर्ण

