<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IBM/3270 Driver - console view.
 *
 * Author(s):
 *   Original 3270 Code क्रम 2.4 written by Riअक्षरd Hitt (UTS Global)
 *   Rewritten क्रम 2.5 by Martin Schwidefsky <schwidefsky@de.ibm.com>
 *     Copyright IBM Corp. 2003, 2009
 */

#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/ebcdic.h>

#समावेश "raw3270.h"
#समावेश "tty3270.h"
#समावेश "ctrlchar.h"

#घोषणा CON3270_OUTPUT_BUFFER_SIZE 1024
#घोषणा CON3270_STRING_PAGES 4

अटल काष्ठा raw3270_fn con3270_fn;

अटल bool स्वतः_update = true;
module_param(स्वतः_update, bool, 0);

/*
 * Main 3270 console view data काष्ठाure.
 */
काष्ठा con3270 अणु
	काष्ठा raw3270_view view;
	काष्ठा list_head मुक्तmem;	/* list of मुक्त memory क्रम strings. */

	/* Output stuff. */
	काष्ठा list_head lines;		/* list of lines. */
	काष्ठा list_head update;	/* list of lines to update. */
	पूर्णांक line_nr;			/* line number क्रम next update. */
	पूर्णांक nr_lines;			/* # lines in list. */
	पूर्णांक nr_up;			/* # lines up in history. */
	अचिन्हित दीर्घ update_flags;	/* Update indication bits. */
	काष्ठा string *cline;		/* current output line. */
	काष्ठा string *status;		/* last line of display. */
	काष्ठा raw3270_request *ग_लिखो;	/* single ग_लिखो request. */
	काष्ठा समयr_list समयr;

	/* Input stuff. */
	काष्ठा string *input;		/* input string क्रम पढ़ो request. */
	काष्ठा raw3270_request *पढ़ो;	/* single पढ़ो request. */
	काष्ठा raw3270_request *kreset;	/* single keyboard reset request. */
	काष्ठा tasklet_काष्ठा पढ़ोlet;	/* tasklet to issue पढ़ो request. */
पूर्ण;

अटल काष्ठा con3270 *condev;

/* con3270->update_flags. See con3270_update क्रम details. */
#घोषणा CON_UPDATE_ERASE	1	/* Use EWRITEA instead of WRITE. */
#घोषणा CON_UPDATE_LIST		2	/* Update lines in tty3270->update. */
#घोषणा CON_UPDATE_STATUS	4	/* Update status line. */
#घोषणा CON_UPDATE_ALL		8	/* Recreate screen. */

अटल व्योम con3270_update(काष्ठा समयr_list *);

/*
 * Setup समयout क्रम a device. On समयout trigger an update.
 */
अटल व्योम con3270_set_समयr(काष्ठा con3270 *cp, पूर्णांक expires)
अणु
	अगर (expires == 0)
		del_समयr(&cp->समयr);
	अन्यथा
		mod_समयr(&cp->समयr, jअगरfies + expires);
पूर्ण

/*
 * The status line is the last line of the screen. It shows the string
 * "console view" in the lower left corner and "Running"/"More..."/"Holding"
 * in the lower right corner of the screen.
 */
अटल व्योम
con3270_update_status(काष्ठा con3270 *cp)
अणु
	अक्षर *str;

	str = (cp->nr_up != 0) ? "History" : "Running";
	स_नकल(cp->status->string + 24, str, 7);
	codepage_convert(cp->view.ascebc, cp->status->string + 24, 7);
	cp->update_flags |= CON_UPDATE_STATUS;
पूर्ण

अटल व्योम
con3270_create_status(काष्ठा con3270 *cp)
अणु
	अटल स्थिर अचिन्हित अक्षर blueprपूर्णांक[] =
		अणु TO_SBA, 0, 0, TO_SF,TF_LOG,TO_SA,TAT_COLOR, TAC_GREEN,
		  'c','o','n','s','o','l','e',' ','v','i','e','w',
		  TO_RA,0,0,0,'R','u','n','n','i','n','g',TO_SF,TF_LOG पूर्ण;

	cp->status = alloc_string(&cp->मुक्तmem, माप(blueprपूर्णांक));
	/* Copy blueprपूर्णांक to status line */
	स_नकल(cp->status->string, blueprपूर्णांक, माप(blueprपूर्णांक));
	/* Set TO_RA addresses. */
	raw3270_buffer_address(cp->view.dev, cp->status->string + 1,
			       cp->view.cols * (cp->view.rows - 1));
	raw3270_buffer_address(cp->view.dev, cp->status->string + 21,
			       cp->view.cols * cp->view.rows - 8);
	/* Convert strings to ebcdic. */
	codepage_convert(cp->view.ascebc, cp->status->string + 8, 12);
	codepage_convert(cp->view.ascebc, cp->status->string + 24, 7);
पूर्ण

/*
 * Set output offsets to 3270 datastream fragment of a console string.
 */
अटल व्योम
con3270_update_string(काष्ठा con3270 *cp, काष्ठा string *s, पूर्णांक nr)
अणु
	अगर (s->len < 4) अणु
		/* This indicates a bug, but prपूर्णांकing a warning would
		 * cause a deadlock. */
		वापस;
	पूर्ण
	अगर (s->string[s->len - 4] != TO_RA)
		वापस;
	raw3270_buffer_address(cp->view.dev, s->string + s->len - 3,
			       cp->view.cols * (nr + 1));
पूर्ण

/*
 * Rebuild update list to prपूर्णांक all lines.
 */
अटल व्योम
con3270_rebuild_update(काष्ठा con3270 *cp)
अणु
	काष्ठा string *s, *n;
	पूर्णांक nr;

	/* 
	 * Throw away update list and create a new one,
	 * containing all lines that will fit on the screen.
	 */
	list_क्रम_each_entry_safe(s, n, &cp->update, update)
		list_del_init(&s->update);
	nr = cp->view.rows - 2 + cp->nr_up;
	list_क्रम_each_entry_reverse(s, &cp->lines, list) अणु
		अगर (nr < cp->view.rows - 1)
			list_add(&s->update, &cp->update);
		अगर (--nr < 0)
			अवरोध;
	पूर्ण
	cp->line_nr = 0;
	cp->update_flags |= CON_UPDATE_LIST;
पूर्ण

/*
 * Alloc string क्रम size bytes. Free strings from history अगर necessary.
 */
अटल काष्ठा string *
con3270_alloc_string(काष्ठा con3270 *cp, माप_प्रकार size)
अणु
	काष्ठा string *s, *n;

	s = alloc_string(&cp->मुक्तmem, size);
	अगर (s)
		वापस s;
	list_क्रम_each_entry_safe(s, n, &cp->lines, list) अणु
		list_del(&s->list);
		अगर (!list_empty(&s->update))
			list_del(&s->update);
		cp->nr_lines--;
		अगर (मुक्त_string(&cp->मुक्तmem, s) >= size)
			अवरोध;
	पूर्ण
	s = alloc_string(&cp->मुक्तmem, size);
	BUG_ON(!s);
	अगर (cp->nr_up != 0 && cp->nr_up + cp->view.rows > cp->nr_lines) अणु
		cp->nr_up = cp->nr_lines - cp->view.rows + 1;
		con3270_rebuild_update(cp);
		con3270_update_status(cp);
	पूर्ण
	वापस s;
पूर्ण

/*
 * Write completion callback.
 */
अटल व्योम
con3270_ग_लिखो_callback(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	raw3270_request_reset(rq);
	xchg(&((काष्ठा con3270 *) rq->view)->ग_लिखो, rq);
पूर्ण

/*
 * Update console display.
 */
अटल व्योम
con3270_update(काष्ठा समयr_list *t)
अणु
	काष्ठा con3270 *cp = from_समयr(cp, t, समयr);
	काष्ठा raw3270_request *wrq;
	अक्षर wcc, prolog[6];
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ updated;
	काष्ठा string *s, *n;
	पूर्णांक rc;

	अगर (!स्वतः_update && !raw3270_view_active(&cp->view))
		वापस;
	अगर (cp->view.dev)
		raw3270_activate_view(&cp->view);

	wrq = xchg(&cp->ग_लिखो, 0);
	अगर (!wrq) अणु
		con3270_set_समयr(cp, 1);
		वापस;
	पूर्ण

	spin_lock_irqsave(&cp->view.lock, flags);
	updated = 0;
	अगर (cp->update_flags & CON_UPDATE_ALL) अणु
		con3270_rebuild_update(cp);
		con3270_update_status(cp);
		cp->update_flags = CON_UPDATE_ERASE | CON_UPDATE_LIST |
			CON_UPDATE_STATUS;
	पूर्ण
	अगर (cp->update_flags & CON_UPDATE_ERASE) अणु
		/* Use erase ग_लिखो alternate to initialize display. */
		raw3270_request_set_cmd(wrq, TC_EWRITEA);
		updated |= CON_UPDATE_ERASE;
	पूर्ण अन्यथा
		raw3270_request_set_cmd(wrq, TC_WRITE);

	wcc = TW_NONE;
	raw3270_request_add_data(wrq, &wcc, 1);

	/*
	 * Update status line.
	 */
	अगर (cp->update_flags & CON_UPDATE_STATUS)
		अगर (raw3270_request_add_data(wrq, cp->status->string,
					     cp->status->len) == 0)
			updated |= CON_UPDATE_STATUS;

	अगर (cp->update_flags & CON_UPDATE_LIST) अणु
		prolog[0] = TO_SBA;
		prolog[3] = TO_SA;
		prolog[4] = TAT_COLOR;
		prolog[5] = TAC_TURQ;
		raw3270_buffer_address(cp->view.dev, prolog + 1,
				       cp->view.cols * cp->line_nr);
		raw3270_request_add_data(wrq, prolog, 6);
		/* Write strings in the update list to the screen. */
		list_क्रम_each_entry_safe(s, n, &cp->update, update) अणु
			अगर (s != cp->cline)
				con3270_update_string(cp, s, cp->line_nr);
			अगर (raw3270_request_add_data(wrq, s->string,
						     s->len) != 0)
				अवरोध;
			list_del_init(&s->update);
			अगर (s != cp->cline)
				cp->line_nr++;
		पूर्ण
		अगर (list_empty(&cp->update))
			updated |= CON_UPDATE_LIST;
	पूर्ण
	wrq->callback = con3270_ग_लिखो_callback;
	rc = raw3270_start(&cp->view, wrq);
	अगर (rc == 0) अणु
		cp->update_flags &= ~updated;
		अगर (cp->update_flags)
			con3270_set_समयr(cp, 1);
	पूर्ण अन्यथा अणु
		raw3270_request_reset(wrq);
		xchg(&cp->ग_लिखो, wrq);
	पूर्ण
	spin_unlock_irqrestore(&cp->view.lock, flags);
पूर्ण

/*
 * Read tasklet.
 */
अटल व्योम
con3270_पढ़ो_tasklet(काष्ठा raw3270_request *rrq)
अणु
	अटल अक्षर kreset_data = TW_KR;
	काष्ठा con3270 *cp;
	अचिन्हित दीर्घ flags;
	पूर्णांक nr_up, deactivate;

	cp = (काष्ठा con3270 *) rrq->view;
	spin_lock_irqsave(&cp->view.lock, flags);
	nr_up = cp->nr_up;
	deactivate = 0;
	/* Check aid byte. */
	चयन (cp->input->string[0]) अणु
	हाल 0x7d:	/* enter: jump to bottom. */
		nr_up = 0;
		अवरोध;
	हाल 0xf3:	/* PF3: deactivate the console view. */
		deactivate = 1;
		अवरोध;
	हाल 0x6d:	/* clear: start from scratch. */
		cp->update_flags = CON_UPDATE_ALL;
		con3270_set_समयr(cp, 1);
		अवरोध;
	हाल 0xf7:	/* PF7: करो a page up in the console log. */
		nr_up += cp->view.rows - 2;
		अगर (nr_up + cp->view.rows - 1 > cp->nr_lines) अणु
			nr_up = cp->nr_lines - cp->view.rows + 1;
			अगर (nr_up < 0)
				nr_up = 0;
		पूर्ण
		अवरोध;
	हाल 0xf8:	/* PF8: करो a page करोwn in the console log. */
		nr_up -= cp->view.rows - 2;
		अगर (nr_up < 0)
			nr_up = 0;
		अवरोध;
	पूर्ण
	अगर (nr_up != cp->nr_up) अणु
		cp->nr_up = nr_up;
		con3270_rebuild_update(cp);
		con3270_update_status(cp);
		con3270_set_समयr(cp, 1);
	पूर्ण
	spin_unlock_irqrestore(&cp->view.lock, flags);

	/* Start keyboard reset command. */
	raw3270_request_reset(cp->kreset);
	raw3270_request_set_cmd(cp->kreset, TC_WRITE);
	raw3270_request_add_data(cp->kreset, &kreset_data, 1);
	raw3270_start(&cp->view, cp->kreset);

	अगर (deactivate)
		raw3270_deactivate_view(&cp->view);

	raw3270_request_reset(rrq);
	xchg(&cp->पढ़ो, rrq);
	raw3270_put_view(&cp->view);
पूर्ण

/*
 * Read request completion callback.
 */
अटल व्योम
con3270_पढ़ो_callback(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	raw3270_get_view(rq->view);
	/* Schedule tasklet to pass input to tty. */
	tasklet_schedule(&((काष्ठा con3270 *) rq->view)->पढ़ोlet);
पूर्ण

/*
 * Issue a पढ़ो request. Called only from पूर्णांकerrupt function.
 */
अटल व्योम
con3270_issue_पढ़ो(काष्ठा con3270 *cp)
अणु
	काष्ठा raw3270_request *rrq;
	पूर्णांक rc;

	rrq = xchg(&cp->पढ़ो, 0);
	अगर (!rrq)
		/* Read alपढ़ोy scheduled. */
		वापस;
	rrq->callback = con3270_पढ़ो_callback;
	rrq->callback_data = cp;
	raw3270_request_set_cmd(rrq, TC_READMOD);
	raw3270_request_set_data(rrq, cp->input->string, cp->input->len);
	/* Issue the पढ़ो modअगरied request. */
	rc = raw3270_start_irq(&cp->view, rrq);
	अगर (rc)
		raw3270_request_reset(rrq);
पूर्ण

/*
 * Switch to the console view.
 */
अटल पूर्णांक
con3270_activate(काष्ठा raw3270_view *view)
अणु
	काष्ठा con3270 *cp;

	cp = (काष्ठा con3270 *) view;
	cp->update_flags = CON_UPDATE_ALL;
	con3270_set_समयr(cp, 1);
	वापस 0;
पूर्ण

अटल व्योम
con3270_deactivate(काष्ठा raw3270_view *view)
अणु
	काष्ठा con3270 *cp;

	cp = (काष्ठा con3270 *) view;
	del_समयr(&cp->समयr);
पूर्ण

अटल व्योम
con3270_irq(काष्ठा con3270 *cp, काष्ठा raw3270_request *rq, काष्ठा irb *irb)
अणु
	/* Handle ATTN. Schedule tasklet to पढ़ो aid. */
	अगर (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION)
		con3270_issue_पढ़ो(cp);

	अगर (rq) अणु
		अगर (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
			rq->rc = -EIO;
		अन्यथा
			/* Normal end. Copy residual count. */
			rq->rescnt = irb->scsw.cmd.count;
	पूर्ण अन्यथा अगर (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) अणु
		/* Interrupt without an outstanding request -> update all */
		cp->update_flags = CON_UPDATE_ALL;
		con3270_set_समयr(cp, 1);
	पूर्ण
पूर्ण

/* Console view to a 3270 device. */
अटल काष्ठा raw3270_fn con3270_fn = अणु
	.activate = con3270_activate,
	.deactivate = con3270_deactivate,
	.पूर्णांकv = (व्योम *) con3270_irq
पूर्ण;

अटल अंतरभूत व्योम
con3270_cline_add(काष्ठा con3270 *cp)
अणु
	अगर (!list_empty(&cp->cline->list))
		/* Alपढ़ोy added. */
		वापस;
	list_add_tail(&cp->cline->list, &cp->lines);
	cp->nr_lines++;
	con3270_rebuild_update(cp);
पूर्ण

अटल अंतरभूत व्योम
con3270_cline_insert(काष्ठा con3270 *cp, अचिन्हित अक्षर c)
अणु
	cp->cline->string[cp->cline->len++] = 
		cp->view.ascebc[(c < ' ') ? ' ' : c];
	अगर (list_empty(&cp->cline->update)) अणु
		list_add_tail(&cp->cline->update, &cp->update);
		cp->update_flags |= CON_UPDATE_LIST;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
con3270_cline_end(काष्ठा con3270 *cp)
अणु
	काष्ठा string *s;
	अचिन्हित पूर्णांक size;

	/* Copy cline. */
	size = (cp->cline->len < cp->view.cols - 5) ?
		cp->cline->len + 4 : cp->view.cols;
	s = con3270_alloc_string(cp, size);
	स_नकल(s->string, cp->cline->string, cp->cline->len);
	अगर (cp->cline->len < cp->view.cols - 5) अणु
		s->string[s->len - 4] = TO_RA;
		s->string[s->len - 1] = 0;
	पूर्ण अन्यथा अणु
		जबतक (--size >= cp->cline->len)
			s->string[size] = cp->view.ascebc[' '];
	पूर्ण
	/* Replace cline with allocated line s and reset cline. */
	list_add(&s->list, &cp->cline->list);
	list_del_init(&cp->cline->list);
	अगर (!list_empty(&cp->cline->update)) अणु
		list_add(&s->update, &cp->cline->update);
		list_del_init(&cp->cline->update);
	पूर्ण
	cp->cline->len = 0;
पूर्ण

/*
 * Write a string to the 3270 console
 */
अटल व्योम
con3270_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *str, अचिन्हित पूर्णांक count)
अणु
	काष्ठा con3270 *cp;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर c;

	cp = condev;
	spin_lock_irqsave(&cp->view.lock, flags);
	जबतक (count-- > 0) अणु
		c = *str++;
		अगर (cp->cline->len == 0)
			con3270_cline_add(cp);
		अगर (c != '\n')
			con3270_cline_insert(cp, c);
		अगर (c == '\n' || cp->cline->len >= cp->view.cols)
			con3270_cline_end(cp);
	पूर्ण
	/* Setup समयr to output current console buffer after 1/10 second */
	cp->nr_up = 0;
	अगर (cp->view.dev && !समयr_pending(&cp->समयr))
		con3270_set_समयr(cp, HZ/10);
	spin_unlock_irqrestore(&cp->view.lock,flags);
पूर्ण

अटल काष्ठा tty_driver *
con3270_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = c->index;
	वापस tty3270_driver;
पूर्ण

/*
 * Wait क्रम end of ग_लिखो request.
 */
अटल व्योम
con3270_रुको_ग_लिखो(काष्ठा con3270 *cp)
अणु
	जबतक (!cp->ग_लिखो) अणु
		raw3270_रुको_cons_dev(cp->view.dev);
		barrier();
	पूर्ण
पूर्ण

/*
 * panic() calls con3270_flush through a panic_notअगरier
 * beक्रमe the प्रणाली enters a disabled, endless loop.
 */
अटल व्योम
con3270_flush(व्योम)
अणु
	काष्ठा con3270 *cp;
	अचिन्हित दीर्घ flags;

	cp = condev;
	अगर (!cp->view.dev)
		वापस;
	raw3270_activate_view(&cp->view);
	spin_lock_irqsave(&cp->view.lock, flags);
	con3270_रुको_ग_लिखो(cp);
	cp->nr_up = 0;
	con3270_rebuild_update(cp);
	con3270_update_status(cp);
	जबतक (cp->update_flags != 0) अणु
		spin_unlock_irqrestore(&cp->view.lock, flags);
		con3270_update(&cp->समयr);
		spin_lock_irqsave(&cp->view.lock, flags);
		con3270_रुको_ग_लिखो(cp);
	पूर्ण
	spin_unlock_irqrestore(&cp->view.lock, flags);
पूर्ण

अटल पूर्णांक con3270_notअगरy(काष्ठा notअगरier_block *self,
			  अचिन्हित दीर्घ event, व्योम *data)
अणु
	con3270_flush();
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block on_panic_nb = अणु
	.notअगरier_call = con3270_notअगरy,
	.priority = 0,
पूर्ण;

अटल काष्ठा notअगरier_block on_reboot_nb = अणु
	.notअगरier_call = con3270_notअगरy,
	.priority = 0,
पूर्ण;

/*
 *  The console काष्ठाure क्रम the 3270 console
 */
अटल काष्ठा console con3270 = अणु
	.name	 = "tty3270",
	.ग_लिखो	 = con3270_ग_लिखो,
	.device	 = con3270_device,
	.flags	 = CON_PRINTBUFFER,
पूर्ण;

/*
 * 3270 console initialization code called from console_init().
 */
अटल पूर्णांक __init
con3270_init(व्योम)
अणु
	काष्ठा raw3270 *rp;
	व्योम *cbuf;
	पूर्णांक i;

	/* Check अगर 3270 is to be the console */
	अगर (!CONSOLE_IS_3270)
		वापस -ENODEV;

	/* Set the console mode क्रम VM */
	अगर (MACHINE_IS_VM) अणु
		cpcmd("TERM CONMODE 3270", शून्य, 0, शून्य);
		cpcmd("TERM AUTOCR OFF", शून्य, 0, शून्य);
	पूर्ण

	rp = raw3270_setup_console();
	अगर (IS_ERR(rp))
		वापस PTR_ERR(rp);

	condev = kzalloc(माप(काष्ठा con3270), GFP_KERNEL | GFP_DMA);
	अगर (!condev)
		वापस -ENOMEM;
	condev->view.dev = rp;

	condev->पढ़ो = raw3270_request_alloc(0);
	condev->पढ़ो->callback = con3270_पढ़ो_callback;
	condev->पढ़ो->callback_data = condev;
	condev->ग_लिखो = raw3270_request_alloc(CON3270_OUTPUT_BUFFER_SIZE);
	condev->kreset = raw3270_request_alloc(1);

	INIT_LIST_HEAD(&condev->lines);
	INIT_LIST_HEAD(&condev->update);
	समयr_setup(&condev->समयr, con3270_update, 0);
	tasklet_init(&condev->पढ़ोlet, 
		     (व्योम (*)(अचिन्हित दीर्घ)) con3270_पढ़ो_tasklet,
		     (अचिन्हित दीर्घ) condev->पढ़ो);

	raw3270_add_view(&condev->view, &con3270_fn, 1, RAW3270_VIEW_LOCK_IRQ);

	INIT_LIST_HEAD(&condev->मुक्तmem);
	क्रम (i = 0; i < CON3270_STRING_PAGES; i++) अणु
		cbuf = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
		add_string_memory(&condev->मुक्तmem, cbuf, PAGE_SIZE);
	पूर्ण
	condev->cline = alloc_string(&condev->मुक्तmem, condev->view.cols);
	condev->cline->len = 0;
	con3270_create_status(condev);
	condev->input = alloc_string(&condev->मुक्तmem, 80);
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &on_panic_nb);
	रेजिस्टर_reboot_notअगरier(&on_reboot_nb);
	रेजिस्टर_console(&con3270);
	वापस 0;
पूर्ण

console_initcall(con3270_init);
