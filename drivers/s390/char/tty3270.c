<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    IBM/3270 Driver - tty functions.
 *
 *  Author(s):
 *    Original 3270 Code क्रम 2.4 written by Riअक्षरd Hitt (UTS Global)
 *    Rewritten क्रम 2.5 by Martin Schwidefsky <schwidefsky@de.ibm.com>
 *	-- Copyright IBM Corp. 2003
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/tty.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>
#समावेश <linux/compat.h>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ebcdic.h>
#समावेश <linux/uaccess.h>

#समावेश "raw3270.h"
#समावेश "tty3270.h"
#समावेश "keyboard.h"

#घोषणा TTY3270_CHAR_BUF_SIZE 256
#घोषणा TTY3270_OUTPUT_BUFFER_SIZE 1024
#घोषणा TTY3270_STRING_PAGES 5

काष्ठा tty_driver *tty3270_driver;
अटल पूर्णांक tty3270_max_index;

अटल काष्ठा raw3270_fn tty3270_fn;

काष्ठा tty3270_cell अणु
	अचिन्हित अक्षर अक्षरacter;
	अचिन्हित अक्षर highlight;
	अचिन्हित अक्षर f_color;
पूर्ण;

काष्ठा tty3270_line अणु
	काष्ठा tty3270_cell *cells;
	पूर्णांक len;
पूर्ण;

#घोषणा ESCAPE_NPAR 8

/*
 * The मुख्य tty view data काष्ठाure.
 * FIXME:
 * 1) describe line orientation & lines list concept against screen
 * 2) describe conversion of screen to lines
 * 3) describe line क्रमmat.
 */
काष्ठा tty3270 अणु
	काष्ठा raw3270_view view;
	काष्ठा tty_port port;
	व्योम **मुक्तmem_pages;		/* Array of pages used क्रम मुक्तmem. */
	काष्ठा list_head मुक्तmem;	/* List of मुक्त memory क्रम strings. */

	/* Output stuff. */
	काष्ठा list_head lines;		/* List of lines. */
	काष्ठा list_head update;	/* List of lines to update. */
	अचिन्हित अक्षर wcc;		/* Write control अक्षरacter. */
	पूर्णांक nr_lines;			/* # lines in list. */
	पूर्णांक nr_up;			/* # lines up in history. */
	अचिन्हित दीर्घ update_flags;	/* Update indication bits. */
	काष्ठा string *status;		/* Lower right of display. */
	काष्ठा raw3270_request *ग_लिखो;	/* Single ग_लिखो request. */
	काष्ठा समयr_list समयr;	/* Output delay समयr. */

	/* Current tty screen. */
	अचिन्हित पूर्णांक cx, cy;		/* Current output position. */
	अचिन्हित पूर्णांक highlight;		/* Blink/reverse/underscore */
	अचिन्हित पूर्णांक f_color;		/* Foreground color */
	काष्ठा tty3270_line *screen;
	अचिन्हित पूर्णांक n_model, n_cols, n_rows;	/* New model & size */
	काष्ठा work_काष्ठा resize_work;

	/* Input stuff. */
	काष्ठा string *prompt;		/* Output string क्रम input area. */
	काष्ठा string *input;		/* Input string क्रम पढ़ो request. */
	काष्ठा raw3270_request *पढ़ो;	/* Single पढ़ो request. */
	काष्ठा raw3270_request *kreset;	/* Single keyboard reset request. */
	अचिन्हित अक्षर inattr;		/* Visible/invisible input. */
	पूर्णांक throttle, attn;		/* tty throttle/unthrottle. */
	काष्ठा tasklet_काष्ठा पढ़ोlet;	/* Tasklet to issue पढ़ो request. */
	काष्ठा tasklet_काष्ठा hanglet;	/* Tasklet to hang up the tty. */
	काष्ठा kbd_data *kbd;		/* key_maps stuff. */

	/* Escape sequence parsing. */
	पूर्णांक esc_state, esc_ques, esc_npar;
	पूर्णांक esc_par[ESCAPE_NPAR];
	अचिन्हित पूर्णांक saved_cx, saved_cy;
	अचिन्हित पूर्णांक saved_highlight, saved_f_color;

	/* Command recalling. */
	काष्ठा list_head rcl_lines;	/* List of recallable lines. */
	काष्ठा list_head *rcl_walk;	/* Poपूर्णांक in rcl_lines list. */
	पूर्णांक rcl_nr, rcl_max;		/* Number/max number of rcl_lines. */

	/* Character array क्रम put_अक्षर/flush_अक्षरs. */
	अचिन्हित पूर्णांक अक्षर_count;
	अक्षर अक्षर_buf[TTY3270_CHAR_BUF_SIZE];
पूर्ण;

/* tty3270->update_flags. See tty3270_update क्रम details. */
#घोषणा TTY_UPDATE_ERASE	1	/* Use EWRITEA instead of WRITE. */
#घोषणा TTY_UPDATE_LIST		2	/* Update lines in tty3270->update. */
#घोषणा TTY_UPDATE_INPUT	4	/* Update input line. */
#घोषणा TTY_UPDATE_STATUS	8	/* Update status line. */
#घोषणा TTY_UPDATE_ALL		16	/* Recreate screen. */

अटल व्योम tty3270_update(काष्ठा समयr_list *);
अटल व्योम tty3270_resize_work(काष्ठा work_काष्ठा *work);

/*
 * Setup समयout क्रम a device. On समयout trigger an update.
 */
अटल व्योम tty3270_set_समयr(काष्ठा tty3270 *tp, पूर्णांक expires)
अणु
	mod_समयr(&tp->समयr, jअगरfies + expires);
पूर्ण

/*
 * The input line are the two last lines of the screen.
 */
अटल व्योम
tty3270_update_prompt(काष्ठा tty3270 *tp, अक्षर *input, पूर्णांक count)
अणु
	काष्ठा string *line;
	अचिन्हित पूर्णांक off;

	line = tp->prompt;
	अगर (count != 0)
		line->string[5] = TF_INMDT;
	अन्यथा
		line->string[5] = tp->inattr;
	अगर (count > tp->view.cols * 2 - 11)
		count = tp->view.cols * 2 - 11;
	स_नकल(line->string + 6, input, count);
	line->string[6 + count] = TO_IC;
	/* Clear to end of input line. */
	अगर (count < tp->view.cols * 2 - 11) अणु
		line->string[7 + count] = TO_RA;
		line->string[10 + count] = 0;
		off = tp->view.cols * tp->view.rows - 9;
		raw3270_buffer_address(tp->view.dev, line->string+count+8, off);
		line->len = 11 + count;
	पूर्ण अन्यथा
		line->len = 7 + count;
	tp->update_flags |= TTY_UPDATE_INPUT;
पूर्ण

अटल व्योम
tty3270_create_prompt(काष्ठा tty3270 *tp)
अणु
	अटल स्थिर अचिन्हित अक्षर blueprपूर्णांक[] =
		अणु TO_SBA, 0, 0, 0x6e, TO_SF, TF_INPUT,
		  /* empty input string */
		  TO_IC, TO_RA, 0, 0, 0 पूर्ण;
	काष्ठा string *line;
	अचिन्हित पूर्णांक offset;

	line = alloc_string(&tp->मुक्तmem,
			    माप(blueprपूर्णांक) + tp->view.cols * 2 - 9);
	tp->prompt = line;
	tp->inattr = TF_INPUT;
	/* Copy blueprपूर्णांक to status line */
	स_नकल(line->string, blueprपूर्णांक, माप(blueprपूर्णांक));
	line->len = माप(blueprपूर्णांक);
	/* Set output offsets. */
	offset = tp->view.cols * (tp->view.rows - 2);
	raw3270_buffer_address(tp->view.dev, line->string + 1, offset);
	offset = tp->view.cols * tp->view.rows - 9;
	raw3270_buffer_address(tp->view.dev, line->string + 8, offset);

	/* Allocate input string क्रम पढ़ोing. */
	tp->input = alloc_string(&tp->मुक्तmem, tp->view.cols * 2 - 9 + 6);
पूर्ण

/*
 * The status line is the last line of the screen. It shows the string
 * "Running"/"Holding" in the lower right corner of the screen.
 */
अटल व्योम
tty3270_update_status(काष्ठा tty3270 * tp)
अणु
	अक्षर *str;

	str = (tp->nr_up != 0) ? "History" : "Running";
	स_नकल(tp->status->string + 8, str, 7);
	codepage_convert(tp->view.ascebc, tp->status->string + 8, 7);
	tp->update_flags |= TTY_UPDATE_STATUS;
पूर्ण

अटल व्योम
tty3270_create_status(काष्ठा tty3270 * tp)
अणु
	अटल स्थिर अचिन्हित अक्षर blueprपूर्णांक[] =
		अणु TO_SBA, 0, 0, TO_SF, TF_LOG, TO_SA, TAT_COLOR, TAC_GREEN,
		  0, 0, 0, 0, 0, 0, 0, TO_SF, TF_LOG, TO_SA, TAT_COLOR,
		  TAC_RESET पूर्ण;
	काष्ठा string *line;
	अचिन्हित पूर्णांक offset;

	line = alloc_string(&tp->मुक्तmem,माप(blueprपूर्णांक));
	tp->status = line;
	/* Copy blueprपूर्णांक to status line */
	स_नकल(line->string, blueprपूर्णांक, माप(blueprपूर्णांक));
	/* Set address to start of status string (= last 9 अक्षरacters). */
	offset = tp->view.cols * tp->view.rows - 9;
	raw3270_buffer_address(tp->view.dev, line->string + 1, offset);
पूर्ण

/*
 * Set output offsets to 3270 datastream fragment of a tty string.
 * (TO_SBA offset at the start and TO_RA offset at the end of the string)
 */
अटल व्योम
tty3270_update_string(काष्ठा tty3270 *tp, काष्ठा string *line, पूर्णांक nr)
अणु
	अचिन्हित अक्षर *cp;

	raw3270_buffer_address(tp->view.dev, line->string + 1,
			       tp->view.cols * nr);
	cp = line->string + line->len - 4;
	अगर (*cp == TO_RA)
		raw3270_buffer_address(tp->view.dev, cp + 1,
				       tp->view.cols * (nr + 1));
पूर्ण

/*
 * Rebuild update list to prपूर्णांक all lines.
 */
अटल व्योम
tty3270_rebuild_update(काष्ठा tty3270 *tp)
अणु
	काष्ठा string *s, *n;
	पूर्णांक line, nr_up;

	/* 
	 * Throw away update list and create a new one,
	 * containing all lines that will fit on the screen.
	 */
	list_क्रम_each_entry_safe(s, n, &tp->update, update)
		list_del_init(&s->update);
	line = tp->view.rows - 3;
	nr_up = tp->nr_up;
	list_क्रम_each_entry_reverse(s, &tp->lines, list) अणु
		अगर (nr_up > 0) अणु
			nr_up--;
			जारी;
		पूर्ण
		tty3270_update_string(tp, s, line);
		list_add(&s->update, &tp->update);
		अगर (--line < 0)
			अवरोध;
	पूर्ण
	tp->update_flags |= TTY_UPDATE_LIST;
पूर्ण

/*
 * Alloc string क्रम size bytes. If there is not enough room in
 * मुक्तmem, मुक्त strings until there is room.
 */
अटल काष्ठा string *
tty3270_alloc_string(काष्ठा tty3270 *tp, माप_प्रकार size)
अणु
	काष्ठा string *s, *n;

	s = alloc_string(&tp->मुक्तmem, size);
	अगर (s)
		वापस s;
	list_क्रम_each_entry_safe(s, n, &tp->lines, list) अणु
		BUG_ON(tp->nr_lines <= tp->view.rows - 2);
		list_del(&s->list);
		अगर (!list_empty(&s->update))
			list_del(&s->update);
		tp->nr_lines--;
		अगर (मुक्त_string(&tp->मुक्तmem, s) >= size)
			अवरोध;
	पूर्ण
	s = alloc_string(&tp->मुक्तmem, size);
	BUG_ON(!s);
	अगर (tp->nr_up != 0 &&
	    tp->nr_up + tp->view.rows - 2 >= tp->nr_lines) अणु
		tp->nr_up = tp->nr_lines - tp->view.rows + 2;
		tty3270_rebuild_update(tp);
		tty3270_update_status(tp);
	पूर्ण
	वापस s;
पूर्ण

/*
 * Add an empty line to the list.
 */
अटल व्योम
tty3270_blank_line(काष्ठा tty3270 *tp)
अणु
	अटल स्थिर अचिन्हित अक्षर blueprपूर्णांक[] =
		अणु TO_SBA, 0, 0, TO_SA, TAT_EXTHI, TAX_RESET,
		  TO_SA, TAT_COLOR, TAC_RESET, TO_RA, 0, 0, 0 पूर्ण;
	काष्ठा string *s;

	s = tty3270_alloc_string(tp, माप(blueprपूर्णांक));
	स_नकल(s->string, blueprपूर्णांक, माप(blueprपूर्णांक));
	s->len = माप(blueprपूर्णांक);
	list_add_tail(&s->list, &tp->lines);
	tp->nr_lines++;
	अगर (tp->nr_up != 0)
		tp->nr_up++;
पूर्ण

/*
 * Create a blank screen and हटाओ all lines from the history.
 */
अटल व्योम
tty3270_blank_screen(काष्ठा tty3270 *tp)
अणु
	काष्ठा string *s, *n;
	पूर्णांक i;

	क्रम (i = 0; i < tp->view.rows - 2; i++)
		tp->screen[i].len = 0;
	tp->nr_up = 0;
	list_क्रम_each_entry_safe(s, n, &tp->lines, list) अणु
		list_del(&s->list);
		अगर (!list_empty(&s->update))
			list_del(&s->update);
		tp->nr_lines--;
		मुक्त_string(&tp->मुक्तmem, s);
	पूर्ण
पूर्ण

/*
 * Write request completion callback.
 */
अटल व्योम
tty3270_ग_लिखो_callback(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	काष्ठा tty3270 *tp = container_of(rq->view, काष्ठा tty3270, view);

	अगर (rq->rc != 0) अणु
		/* Write wasn't successful. Refresh all. */
		tp->update_flags = TTY_UPDATE_ALL;
		tty3270_set_समयr(tp, 1);
	पूर्ण
	raw3270_request_reset(rq);
	xchg(&tp->ग_लिखो, rq);
पूर्ण

/*
 * Update 3270 display.
 */
अटल व्योम
tty3270_update(काष्ठा समयr_list *t)
अणु
	काष्ठा tty3270 *tp = from_समयr(tp, t, समयr);
	अटल अक्षर invalid_sba[2] = अणु 0xff, 0xff पूर्ण;
	काष्ठा raw3270_request *wrq;
	अचिन्हित दीर्घ updated;
	काष्ठा string *s, *n;
	अक्षर *sba, *str;
	पूर्णांक rc, len;

	wrq = xchg(&tp->ग_लिखो, 0);
	अगर (!wrq) अणु
		tty3270_set_समयr(tp, 1);
		वापस;
	पूर्ण

	spin_lock(&tp->view.lock);
	updated = 0;
	अगर (tp->update_flags & TTY_UPDATE_ALL) अणु
		tty3270_rebuild_update(tp);
		tty3270_update_status(tp);
		tp->update_flags = TTY_UPDATE_ERASE | TTY_UPDATE_LIST |
			TTY_UPDATE_INPUT | TTY_UPDATE_STATUS;
	पूर्ण
	अगर (tp->update_flags & TTY_UPDATE_ERASE) अणु
		/* Use erase ग_लिखो alternate to erase display. */
		raw3270_request_set_cmd(wrq, TC_EWRITEA);
		updated |= TTY_UPDATE_ERASE;
	पूर्ण अन्यथा
		raw3270_request_set_cmd(wrq, TC_WRITE);

	raw3270_request_add_data(wrq, &tp->wcc, 1);
	tp->wcc = TW_NONE;

	/*
	 * Update status line.
	 */
	अगर (tp->update_flags & TTY_UPDATE_STATUS)
		अगर (raw3270_request_add_data(wrq, tp->status->string,
					     tp->status->len) == 0)
			updated |= TTY_UPDATE_STATUS;

	/*
	 * Write input line.
	 */
	अगर (tp->update_flags & TTY_UPDATE_INPUT)
		अगर (raw3270_request_add_data(wrq, tp->prompt->string,
					     tp->prompt->len) == 0)
			updated |= TTY_UPDATE_INPUT;

	sba = invalid_sba;
	
	अगर (tp->update_flags & TTY_UPDATE_LIST) अणु
		/* Write strings in the update list to the screen. */
		list_क्रम_each_entry_safe(s, n, &tp->update, update) अणु
			str = s->string;
			len = s->len;
			/*
			 * Skip TO_SBA at the start of the string अगर the
			 * last output position matches the start address
			 * of this line.
			 */
			अगर (s->string[1] == sba[0] && s->string[2] == sba[1]) अणु
				str += 3;
				len -= 3;
			पूर्ण
			अगर (raw3270_request_add_data(wrq, str, len) != 0)
				अवरोध;
			list_del_init(&s->update);
			अगर (s->string[s->len - 4] == TO_RA)
				sba = s->string + s->len - 3;
			अन्यथा
				sba = invalid_sba;
		पूर्ण
		अगर (list_empty(&tp->update))
			updated |= TTY_UPDATE_LIST;
	पूर्ण
	wrq->callback = tty3270_ग_लिखो_callback;
	rc = raw3270_start(&tp->view, wrq);
	अगर (rc == 0) अणु
		tp->update_flags &= ~updated;
		अगर (tp->update_flags)
			tty3270_set_समयr(tp, 1);
	पूर्ण अन्यथा अणु
		raw3270_request_reset(wrq);
		xchg(&tp->ग_लिखो, wrq);
	पूर्ण
	spin_unlock(&tp->view.lock);
पूर्ण

/*
 * Command recalling.
 */
अटल व्योम
tty3270_rcl_add(काष्ठा tty3270 *tp, अक्षर *input, पूर्णांक len)
अणु
	काष्ठा string *s;

	tp->rcl_walk = शून्य;
	अगर (len <= 0)
		वापस;
	अगर (tp->rcl_nr >= tp->rcl_max) अणु
		s = list_entry(tp->rcl_lines.next, काष्ठा string, list);
		list_del(&s->list);
		मुक्त_string(&tp->मुक्तmem, s);
		tp->rcl_nr--;
	पूर्ण
	s = tty3270_alloc_string(tp, len);
	स_नकल(s->string, input, len);
	list_add_tail(&s->list, &tp->rcl_lines);
	tp->rcl_nr++;
पूर्ण

अटल व्योम
tty3270_rcl_backward(काष्ठा kbd_data *kbd)
अणु
	काष्ठा tty3270 *tp = container_of(kbd->port, काष्ठा tty3270, port);
	काष्ठा string *s;

	spin_lock_bh(&tp->view.lock);
	अगर (tp->inattr == TF_INPUT) अणु
		अगर (tp->rcl_walk && tp->rcl_walk->prev != &tp->rcl_lines)
			tp->rcl_walk = tp->rcl_walk->prev;
		अन्यथा अगर (!list_empty(&tp->rcl_lines))
			tp->rcl_walk = tp->rcl_lines.prev;
		s = tp->rcl_walk ? 
			list_entry(tp->rcl_walk, काष्ठा string, list) : शून्य;
		अगर (tp->rcl_walk) अणु
			s = list_entry(tp->rcl_walk, काष्ठा string, list);
			tty3270_update_prompt(tp, s->string, s->len);
		पूर्ण अन्यथा
			tty3270_update_prompt(tp, शून्य, 0);
		tty3270_set_समयr(tp, 1);
	पूर्ण
	spin_unlock_bh(&tp->view.lock);
पूर्ण

/*
 * Deactivate tty view.
 */
अटल व्योम
tty3270_निकास_tty(काष्ठा kbd_data *kbd)
अणु
	काष्ठा tty3270 *tp = container_of(kbd->port, काष्ठा tty3270, port);

	raw3270_deactivate_view(&tp->view);
पूर्ण

/*
 * Scroll क्रमward in history.
 */
अटल व्योम
tty3270_scroll_क्रमward(काष्ठा kbd_data *kbd)
अणु
	काष्ठा tty3270 *tp = container_of(kbd->port, काष्ठा tty3270, port);
	पूर्णांक nr_up;

	spin_lock_bh(&tp->view.lock);
	nr_up = tp->nr_up - tp->view.rows + 2;
	अगर (nr_up < 0)
		nr_up = 0;
	अगर (nr_up != tp->nr_up) अणु
		tp->nr_up = nr_up;
		tty3270_rebuild_update(tp);
		tty3270_update_status(tp);
		tty3270_set_समयr(tp, 1);
	पूर्ण
	spin_unlock_bh(&tp->view.lock);
पूर्ण

/*
 * Scroll backward in history.
 */
अटल व्योम
tty3270_scroll_backward(काष्ठा kbd_data *kbd)
अणु
	काष्ठा tty3270 *tp = container_of(kbd->port, काष्ठा tty3270, port);
	पूर्णांक nr_up;

	spin_lock_bh(&tp->view.lock);
	nr_up = tp->nr_up + tp->view.rows - 2;
	अगर (nr_up + tp->view.rows - 2 > tp->nr_lines)
		nr_up = tp->nr_lines - tp->view.rows + 2;
	अगर (nr_up != tp->nr_up) अणु
		tp->nr_up = nr_up;
		tty3270_rebuild_update(tp);
		tty3270_update_status(tp);
		tty3270_set_समयr(tp, 1);
	पूर्ण
	spin_unlock_bh(&tp->view.lock);
पूर्ण

/*
 * Pass input line to tty.
 */
अटल व्योम
tty3270_पढ़ो_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा raw3270_request *rrq = (काष्ठा raw3270_request *)data;
	अटल अक्षर kreset_data = TW_KR;
	काष्ठा tty3270 *tp = container_of(rrq->view, काष्ठा tty3270, view);
	अक्षर *input;
	पूर्णांक len;

	spin_lock_bh(&tp->view.lock);
	/*
	 * Two AID keys are special: For 0x7d (enter) the input line
	 * has to be emitted to the tty and क्रम 0x6d the screen
	 * needs to be redrawn.
	 */
	input = शून्य;
	len = 0;
	अगर (tp->input->string[0] == 0x7d) अणु
		/* Enter: ग_लिखो input to tty. */
		input = tp->input->string + 6;
		len = tp->input->len - 6 - rrq->rescnt;
		अगर (tp->inattr != TF_INPUTN)
			tty3270_rcl_add(tp, input, len);
		अगर (tp->nr_up > 0) अणु
			tp->nr_up = 0;
			tty3270_rebuild_update(tp);
			tty3270_update_status(tp);
		पूर्ण
		/* Clear input area. */
		tty3270_update_prompt(tp, शून्य, 0);
		tty3270_set_समयr(tp, 1);
	पूर्ण अन्यथा अगर (tp->input->string[0] == 0x6d) अणु
		/* Display has been cleared. Redraw. */
		tp->update_flags = TTY_UPDATE_ALL;
		tty3270_set_समयr(tp, 1);
	पूर्ण
	spin_unlock_bh(&tp->view.lock);

	/* Start keyboard reset command. */
	raw3270_request_reset(tp->kreset);
	raw3270_request_set_cmd(tp->kreset, TC_WRITE);
	raw3270_request_add_data(tp->kreset, &kreset_data, 1);
	raw3270_start(&tp->view, tp->kreset);

	जबतक (len-- > 0)
		kbd_keycode(tp->kbd, *input++);
	/* Emit keycode क्रम AID byte. */
	kbd_keycode(tp->kbd, 256 + tp->input->string[0]);

	raw3270_request_reset(rrq);
	xchg(&tp->पढ़ो, rrq);
	raw3270_put_view(&tp->view);
पूर्ण

/*
 * Read request completion callback.
 */
अटल व्योम
tty3270_पढ़ो_callback(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	काष्ठा tty3270 *tp = container_of(rq->view, काष्ठा tty3270, view);
	raw3270_get_view(rq->view);
	/* Schedule tasklet to pass input to tty. */
	tasklet_schedule(&tp->पढ़ोlet);
पूर्ण

/*
 * Issue a पढ़ो request. Call with device lock.
 */
अटल व्योम
tty3270_issue_पढ़ो(काष्ठा tty3270 *tp, पूर्णांक lock)
अणु
	काष्ठा raw3270_request *rrq;
	पूर्णांक rc;

	rrq = xchg(&tp->पढ़ो, 0);
	अगर (!rrq)
		/* Read alपढ़ोy scheduled. */
		वापस;
	rrq->callback = tty3270_पढ़ो_callback;
	rrq->callback_data = tp;
	raw3270_request_set_cmd(rrq, TC_READMOD);
	raw3270_request_set_data(rrq, tp->input->string, tp->input->len);
	/* Issue the पढ़ो modअगरied request. */
	अगर (lock) अणु
		rc = raw3270_start(&tp->view, rrq);
	पूर्ण अन्यथा
		rc = raw3270_start_irq(&tp->view, rrq);
	अगर (rc) अणु
		raw3270_request_reset(rrq);
		xchg(&tp->पढ़ो, rrq);
	पूर्ण
पूर्ण

/*
 * Hang up the tty
 */
अटल व्योम
tty3270_hangup_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा tty3270 *tp = (काष्ठा tty3270 *)data;
	tty_port_tty_hangup(&tp->port, true);
	raw3270_put_view(&tp->view);
पूर्ण

/*
 * Switch to the tty view.
 */
अटल पूर्णांक
tty3270_activate(काष्ठा raw3270_view *view)
अणु
	काष्ठा tty3270 *tp = container_of(view, काष्ठा tty3270, view);

	tp->update_flags = TTY_UPDATE_ALL;
	tty3270_set_समयr(tp, 1);
	वापस 0;
पूर्ण

अटल व्योम
tty3270_deactivate(काष्ठा raw3270_view *view)
अणु
	काष्ठा tty3270 *tp = container_of(view, काष्ठा tty3270, view);

	del_समयr(&tp->समयr);
पूर्ण

अटल व्योम
tty3270_irq(काष्ठा tty3270 *tp, काष्ठा raw3270_request *rq, काष्ठा irb *irb)
अणु
	/* Handle ATTN. Schedule tasklet to पढ़ो aid. */
	अगर (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) अणु
		अगर (!tp->throttle)
			tty3270_issue_पढ़ो(tp, 0);
		अन्यथा
			tp->attn = 1;
	पूर्ण

	अगर (rq) अणु
		अगर (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) अणु
			rq->rc = -EIO;
			raw3270_get_view(&tp->view);
			tasklet_schedule(&tp->hanglet);
		पूर्ण अन्यथा अणु
			/* Normal end. Copy residual count. */
			rq->rescnt = irb->scsw.cmd.count;
		पूर्ण
	पूर्ण अन्यथा अगर (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) अणु
		/* Interrupt without an outstanding request -> update all */
		tp->update_flags = TTY_UPDATE_ALL;
		tty3270_set_समयr(tp, 1);
	पूर्ण
पूर्ण

/*
 * Allocate tty3270 काष्ठाure.
 */
अटल काष्ठा tty3270 *
tty3270_alloc_view(व्योम)
अणु
	काष्ठा tty3270 *tp;
	पूर्णांक pages;

	tp = kzalloc(माप(काष्ठा tty3270), GFP_KERNEL);
	अगर (!tp)
		जाओ out_err;
	tp->मुक्तmem_pages =
		kदो_स्मृति_array(TTY3270_STRING_PAGES, माप(व्योम *),
			      GFP_KERNEL);
	अगर (!tp->मुक्तmem_pages)
		जाओ out_tp;
	INIT_LIST_HEAD(&tp->मुक्तmem);
	INIT_LIST_HEAD(&tp->lines);
	INIT_LIST_HEAD(&tp->update);
	INIT_LIST_HEAD(&tp->rcl_lines);
	tp->rcl_max = 20;

	क्रम (pages = 0; pages < TTY3270_STRING_PAGES; pages++) अणु
		tp->मुक्तmem_pages[pages] = (व्योम *)
			__get_मुक्त_pages(GFP_KERNEL|GFP_DMA, 0);
		अगर (!tp->मुक्तmem_pages[pages])
			जाओ out_pages;
		add_string_memory(&tp->मुक्तmem,
				  tp->मुक्तmem_pages[pages], PAGE_SIZE);
	पूर्ण
	tp->ग_लिखो = raw3270_request_alloc(TTY3270_OUTPUT_BUFFER_SIZE);
	अगर (IS_ERR(tp->ग_लिखो))
		जाओ out_pages;
	tp->पढ़ो = raw3270_request_alloc(0);
	अगर (IS_ERR(tp->पढ़ो))
		जाओ out_ग_लिखो;
	tp->kreset = raw3270_request_alloc(1);
	अगर (IS_ERR(tp->kreset))
		जाओ out_पढ़ो;
	tp->kbd = kbd_alloc();
	अगर (!tp->kbd)
		जाओ out_reset;

	tty_port_init(&tp->port);
	समयr_setup(&tp->समयr, tty3270_update, 0);
	tasklet_init(&tp->पढ़ोlet, tty3270_पढ़ो_tasklet,
		     (अचिन्हित दीर्घ) tp->पढ़ो);
	tasklet_init(&tp->hanglet, tty3270_hangup_tasklet,
		     (अचिन्हित दीर्घ) tp);
	INIT_WORK(&tp->resize_work, tty3270_resize_work);

	वापस tp;

out_reset:
	raw3270_request_मुक्त(tp->kreset);
out_पढ़ो:
	raw3270_request_मुक्त(tp->पढ़ो);
out_ग_लिखो:
	raw3270_request_मुक्त(tp->ग_लिखो);
out_pages:
	जबतक (pages--)
		मुक्त_pages((अचिन्हित दीर्घ) tp->मुक्तmem_pages[pages], 0);
	kमुक्त(tp->मुक्तmem_pages);
	tty_port_destroy(&tp->port);
out_tp:
	kमुक्त(tp);
out_err:
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * Free tty3270 काष्ठाure.
 */
अटल व्योम
tty3270_मुक्त_view(काष्ठा tty3270 *tp)
अणु
	पूर्णांक pages;

	kbd_मुक्त(tp->kbd);
	raw3270_request_मुक्त(tp->kreset);
	raw3270_request_मुक्त(tp->पढ़ो);
	raw3270_request_मुक्त(tp->ग_लिखो);
	क्रम (pages = 0; pages < TTY3270_STRING_PAGES; pages++)
		मुक्त_pages((अचिन्हित दीर्घ) tp->मुक्तmem_pages[pages], 0);
	kमुक्त(tp->मुक्तmem_pages);
	tty_port_destroy(&tp->port);
	kमुक्त(tp);
पूर्ण

/*
 * Allocate tty3270 screen.
 */
अटल काष्ठा tty3270_line *
tty3270_alloc_screen(अचिन्हित पूर्णांक rows, अचिन्हित पूर्णांक cols)
अणु
	काष्ठा tty3270_line *screen;
	अचिन्हित दीर्घ size;
	पूर्णांक lines;

	size = माप(काष्ठा tty3270_line) * (rows - 2);
	screen = kzalloc(size, GFP_KERNEL);
	अगर (!screen)
		जाओ out_err;
	क्रम (lines = 0; lines < rows - 2; lines++) अणु
		size = माप(काष्ठा tty3270_cell) * cols;
		screen[lines].cells = kzalloc(size, GFP_KERNEL);
		अगर (!screen[lines].cells)
			जाओ out_screen;
	पूर्ण
	वापस screen;
out_screen:
	जबतक (lines--)
		kमुक्त(screen[lines].cells);
	kमुक्त(screen);
out_err:
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * Free tty3270 screen.
 */
अटल व्योम
tty3270_मुक्त_screen(काष्ठा tty3270_line *screen, अचिन्हित पूर्णांक rows)
अणु
	पूर्णांक lines;

	क्रम (lines = 0; lines < rows - 2; lines++)
		kमुक्त(screen[lines].cells);
	kमुक्त(screen);
पूर्ण

/*
 * Resize tty3270 screen
 */
अटल व्योम tty3270_resize_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tty3270 *tp = container_of(work, काष्ठा tty3270, resize_work);
	काष्ठा tty3270_line *screen, *oscreen;
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित पूर्णांक orows;
	काष्ठा winsize ws;

	screen = tty3270_alloc_screen(tp->n_rows, tp->n_cols);
	अगर (IS_ERR(screen))
		वापस;
	/* Switch to new output size */
	spin_lock_bh(&tp->view.lock);
	tty3270_blank_screen(tp);
	oscreen = tp->screen;
	orows = tp->view.rows;
	tp->view.model = tp->n_model;
	tp->view.rows = tp->n_rows;
	tp->view.cols = tp->n_cols;
	tp->screen = screen;
	मुक्त_string(&tp->मुक्तmem, tp->prompt);
	मुक्त_string(&tp->मुक्तmem, tp->status);
	tty3270_create_prompt(tp);
	tty3270_create_status(tp);
	जबतक (tp->nr_lines < tp->view.rows - 2)
		tty3270_blank_line(tp);
	tp->update_flags = TTY_UPDATE_ALL;
	spin_unlock_bh(&tp->view.lock);
	tty3270_मुक्त_screen(oscreen, orows);
	tty3270_set_समयr(tp, 1);
	/* Inक्रमmat tty layer about new size */
	tty = tty_port_tty_get(&tp->port);
	अगर (!tty)
		वापस;
	ws.ws_row = tp->view.rows - 2;
	ws.ws_col = tp->view.cols;
	tty_करो_resize(tty, &ws);
	tty_kref_put(tty);
पूर्ण

अटल व्योम
tty3270_resize(काष्ठा raw3270_view *view, पूर्णांक model, पूर्णांक rows, पूर्णांक cols)
अणु
	काष्ठा tty3270 *tp = container_of(view, काष्ठा tty3270, view);

	अगर (tp->n_model == model && tp->n_rows == rows && tp->n_cols == cols)
		वापस;
	tp->n_model = model;
	tp->n_rows = rows;
	tp->n_cols = cols;
	schedule_work(&tp->resize_work);
पूर्ण

/*
 * Unlink tty3270 data काष्ठाure from tty.
 */
अटल व्योम
tty3270_release(काष्ठा raw3270_view *view)
अणु
	काष्ठा tty3270 *tp = container_of(view, काष्ठा tty3270, view);
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&tp->port);

	अगर (tty) अणु
		tty->driver_data = शून्य;
		tty_port_tty_set(&tp->port, शून्य);
		tty_hangup(tty);
		raw3270_put_view(&tp->view);
		tty_kref_put(tty);
	पूर्ण
पूर्ण

/*
 * Free tty3270 data काष्ठाure
 */
अटल व्योम
tty3270_मुक्त(काष्ठा raw3270_view *view)
अणु
	काष्ठा tty3270 *tp = container_of(view, काष्ठा tty3270, view);

	del_समयr_sync(&tp->समयr);
	tty3270_मुक्त_screen(tp->screen, tp->view.rows);
	tty3270_मुक्त_view(tp);
पूर्ण

/*
 * Delayed मुक्तing of tty3270 views.
 */
अटल व्योम
tty3270_del_views(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = RAW3270_FIRSTMINOR; i <= tty3270_max_index; i++) अणु
		काष्ठा raw3270_view *view = raw3270_find_view(&tty3270_fn, i);
		अगर (!IS_ERR(view))
			raw3270_del_view(view);
	पूर्ण
पूर्ण

अटल काष्ठा raw3270_fn tty3270_fn = अणु
	.activate = tty3270_activate,
	.deactivate = tty3270_deactivate,
	.पूर्णांकv = (व्योम *) tty3270_irq,
	.release = tty3270_release,
	.मुक्त = tty3270_मुक्त,
	.resize = tty3270_resize
पूर्ण;

/*
 * This routine is called whenever a 3270 tty is खोलोed first समय.
 */
अटल पूर्णांक tty3270_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा raw3270_view *view;
	काष्ठा tty3270 *tp;
	पूर्णांक i, rc;

	/* Check अगर the tty3270 is alपढ़ोy there. */
	view = raw3270_find_view(&tty3270_fn, tty->index + RAW3270_FIRSTMINOR);
	अगर (!IS_ERR(view)) अणु
		tp = container_of(view, काष्ठा tty3270, view);
		tty->driver_data = tp;
		tty->winsize.ws_row = tp->view.rows - 2;
		tty->winsize.ws_col = tp->view.cols;
		tp->inattr = TF_INPUT;
		जाओ port_install;
	पूर्ण
	अगर (tty3270_max_index < tty->index + 1)
		tty3270_max_index = tty->index + 1;

	/* Allocate tty3270 काष्ठाure on first खोलो. */
	tp = tty3270_alloc_view();
	अगर (IS_ERR(tp))
		वापस PTR_ERR(tp);

	rc = raw3270_add_view(&tp->view, &tty3270_fn,
			      tty->index + RAW3270_FIRSTMINOR,
			      RAW3270_VIEW_LOCK_BH);
	अगर (rc) अणु
		tty3270_मुक्त_view(tp);
		वापस rc;
	पूर्ण

	tp->screen = tty3270_alloc_screen(tp->view.rows, tp->view.cols);
	अगर (IS_ERR(tp->screen)) अणु
		rc = PTR_ERR(tp->screen);
		raw3270_put_view(&tp->view);
		raw3270_del_view(&tp->view);
		tty3270_मुक्त_view(tp);
		वापस rc;
	पूर्ण

	tty->winsize.ws_row = tp->view.rows - 2;
	tty->winsize.ws_col = tp->view.cols;

	tty3270_create_prompt(tp);
	tty3270_create_status(tp);
	tty3270_update_status(tp);

	/* Create blank line क्रम every line in the tty output area. */
	क्रम (i = 0; i < tp->view.rows - 2; i++)
		tty3270_blank_line(tp);

	tp->kbd->port = &tp->port;
	tp->kbd->fn_handler[KVAL(K_INCRCONSOLE)] = tty3270_निकास_tty;
	tp->kbd->fn_handler[KVAL(K_SCROLLBACK)] = tty3270_scroll_backward;
	tp->kbd->fn_handler[KVAL(K_SCROLLFORW)] = tty3270_scroll_क्रमward;
	tp->kbd->fn_handler[KVAL(K_CONS)] = tty3270_rcl_backward;
	kbd_ascebc(tp->kbd, tp->view.ascebc);

	raw3270_activate_view(&tp->view);

port_install:
	rc = tty_port_install(&tp->port, driver, tty);
	अगर (rc) अणु
		raw3270_put_view(&tp->view);
		वापस rc;
	पूर्ण

	tty->driver_data = tp;

	वापस 0;
पूर्ण

/*
 * This routine is called whenever a 3270 tty is खोलोed.
 */
अटल पूर्णांक
tty3270_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा tty3270 *tp = tty->driver_data;
	काष्ठा tty_port *port = &tp->port;

	port->count++;
	tty_port_tty_set(port, tty);
	वापस 0;
पूर्ण

/*
 * This routine is called when the 3270 tty is बंदd. We रुको
 * क्रम the reमुख्यing request to be completed. Then we clean up.
 */
अटल व्योम
tty3270_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा tty3270 *tp = tty->driver_data;

	अगर (tty->count > 1)
		वापस;
	अगर (tp)
		tty_port_tty_set(&tp->port, शून्य);
पूर्ण

अटल व्योम tty3270_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty3270 *tp = tty->driver_data;

	अगर (tp) अणु
		tty->driver_data = शून्य;
		raw3270_put_view(&tp->view);
	पूर्ण
पूर्ण

/*
 * We always have room.
 */
अटल पूर्णांक
tty3270_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	वापस पूर्णांक_उच्च;
पूर्ण

/*
 * Insert अक्षरacter पूर्णांकo the screen at the current position with the
 * current color and highlight. This function करोes NOT करो cursor movement.
 */
अटल व्योम tty3270_put_अक्षरacter(काष्ठा tty3270 *tp, अक्षर ch)
अणु
	काष्ठा tty3270_line *line;
	काष्ठा tty3270_cell *cell;

	line = tp->screen + tp->cy;
	अगर (line->len <= tp->cx) अणु
		जबतक (line->len < tp->cx) अणु
			cell = line->cells + line->len;
			cell->अक्षरacter = tp->view.ascebc[' '];
			cell->highlight = tp->highlight;
			cell->f_color = tp->f_color;
			line->len++;
		पूर्ण
		line->len++;
	पूर्ण
	cell = line->cells + tp->cx;
	cell->अक्षरacter = tp->view.ascebc[(अचिन्हित पूर्णांक) ch];
	cell->highlight = tp->highlight;
	cell->f_color = tp->f_color;
पूर्ण

/*
 * Convert a tty3270_line to a 3270 data fragment usable क्रम output.
 */
अटल व्योम
tty3270_convert_line(काष्ठा tty3270 *tp, पूर्णांक line_nr)
अणु
	काष्ठा tty3270_line *line;
	काष्ठा tty3270_cell *cell;
	काष्ठा string *s, *n;
	अचिन्हित अक्षर highlight;
	अचिन्हित अक्षर f_color;
	अक्षर *cp;
	पूर्णांक flen, i;

	/* Determine how दीर्घ the fragment will be. */
	flen = 3;		/* Prefix (TO_SBA). */
	line = tp->screen + line_nr;
	flen += line->len;
	highlight = TAX_RESET;
	f_color = TAC_RESET;
	क्रम (i = 0, cell = line->cells; i < line->len; i++, cell++) अणु
		अगर (cell->highlight != highlight) अणु
			flen += 3;	/* TO_SA to चयन highlight. */
			highlight = cell->highlight;
		पूर्ण
		अगर (cell->f_color != f_color) अणु
			flen += 3;	/* TO_SA to चयन color. */
			f_color = cell->f_color;
		पूर्ण
	पूर्ण
	अगर (highlight != TAX_RESET)
		flen += 3;	/* TO_SA to reset hightlight. */
	अगर (f_color != TAC_RESET)
		flen += 3;	/* TO_SA to reset color. */
	अगर (line->len < tp->view.cols)
		flen += 4;	/* Postfix (TO_RA). */

	/* Find the line in the list. */
	i = tp->view.rows - 2 - line_nr;
	list_क्रम_each_entry_reverse(s, &tp->lines, list)
		अगर (--i <= 0)
			अवरोध;
	/*
	 * Check अगर the line needs to get पुनः_स्मृतिated.
	 */
	अगर (s->len != flen) अणु
		/* Reallocate string. */
		n = tty3270_alloc_string(tp, flen);
		list_add(&n->list, &s->list);
		list_del_init(&s->list);
		अगर (!list_empty(&s->update))
			list_del_init(&s->update);
		मुक्त_string(&tp->मुक्तmem, s);
		s = n;
	पूर्ण

	/* Write 3270 data fragment. */
	cp = s->string;
	*cp++ = TO_SBA;
	*cp++ = 0;
	*cp++ = 0;

	highlight = TAX_RESET;
	f_color = TAC_RESET;
	क्रम (i = 0, cell = line->cells; i < line->len; i++, cell++) अणु
		अगर (cell->highlight != highlight) अणु
			*cp++ = TO_SA;
			*cp++ = TAT_EXTHI;
			*cp++ = cell->highlight;
			highlight = cell->highlight;
		पूर्ण
		अगर (cell->f_color != f_color) अणु
			*cp++ = TO_SA;
			*cp++ = TAT_COLOR;
			*cp++ = cell->f_color;
			f_color = cell->f_color;
		पूर्ण
		*cp++ = cell->अक्षरacter;
	पूर्ण
	अगर (highlight != TAX_RESET) अणु
		*cp++ = TO_SA;
		*cp++ = TAT_EXTHI;
		*cp++ = TAX_RESET;
	पूर्ण
	अगर (f_color != TAC_RESET) अणु
		*cp++ = TO_SA;
		*cp++ = TAT_COLOR;
		*cp++ = TAC_RESET;
	पूर्ण
	अगर (line->len < tp->view.cols) अणु
		*cp++ = TO_RA;
		*cp++ = 0;
		*cp++ = 0;
		*cp++ = 0;
	पूर्ण

	अगर (tp->nr_up + line_nr < tp->view.rows - 2) अणु
		/* Line is currently visible on screen. */
		tty3270_update_string(tp, s, line_nr);
		/* Add line to update list. */
		अगर (list_empty(&s->update)) अणु
			list_add_tail(&s->update, &tp->update);
			tp->update_flags |= TTY_UPDATE_LIST;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Do carriage वापस.
 */
अटल व्योम
tty3270_cr(काष्ठा tty3270 *tp)
अणु
	tp->cx = 0;
पूर्ण

/*
 * Do line feed.
 */
अटल व्योम
tty3270_lf(काष्ठा tty3270 *tp)
अणु
	काष्ठा tty3270_line temp;
	पूर्णांक i;

	tty3270_convert_line(tp, tp->cy);
	अगर (tp->cy < tp->view.rows - 3) अणु
		tp->cy++;
		वापस;
	पूर्ण
	/* Last line just filled up. Add new, blank line. */
	tty3270_blank_line(tp);
	temp = tp->screen[0];
	temp.len = 0;
	क्रम (i = 0; i < tp->view.rows - 3; i++)
		tp->screen[i] = tp->screen[i+1];
	tp->screen[tp->view.rows - 3] = temp;
	tty3270_rebuild_update(tp);
पूर्ण

अटल व्योम
tty3270_ri(काष्ठा tty3270 *tp)
अणु
	अगर (tp->cy > 0) अणु
	    tty3270_convert_line(tp, tp->cy);
	    tp->cy--;
	पूर्ण
पूर्ण

/*
 * Insert अक्षरacters at current position.
 */
अटल व्योम
tty3270_insert_अक्षरacters(काष्ठा tty3270 *tp, पूर्णांक n)
अणु
	काष्ठा tty3270_line *line;
	पूर्णांक k;

	line = tp->screen + tp->cy;
	जबतक (line->len < tp->cx) अणु
		line->cells[line->len].अक्षरacter = tp->view.ascebc[' '];
		line->cells[line->len].highlight = TAX_RESET;
		line->cells[line->len].f_color = TAC_RESET;
		line->len++;
	पूर्ण
	अगर (n > tp->view.cols - tp->cx)
		n = tp->view.cols - tp->cx;
	k = min_t(पूर्णांक, line->len - tp->cx, tp->view.cols - tp->cx - n);
	जबतक (k--)
		line->cells[tp->cx + n + k] = line->cells[tp->cx + k];
	line->len += n;
	अगर (line->len > tp->view.cols)
		line->len = tp->view.cols;
	जबतक (n-- > 0) अणु
		line->cells[tp->cx + n].अक्षरacter = tp->view.ascebc[' '];
		line->cells[tp->cx + n].highlight = tp->highlight;
		line->cells[tp->cx + n].f_color = tp->f_color;
	पूर्ण
पूर्ण

/*
 * Delete अक्षरacters at current position.
 */
अटल व्योम
tty3270_delete_अक्षरacters(काष्ठा tty3270 *tp, पूर्णांक n)
अणु
	काष्ठा tty3270_line *line;
	पूर्णांक i;

	line = tp->screen + tp->cy;
	अगर (line->len <= tp->cx)
		वापस;
	अगर (line->len - tp->cx <= n) अणु
		line->len = tp->cx;
		वापस;
	पूर्ण
	क्रम (i = tp->cx; i + n < line->len; i++)
		line->cells[i] = line->cells[i + n];
	line->len -= n;
पूर्ण

/*
 * Erase अक्षरacters at current position.
 */
अटल व्योम
tty3270_erase_अक्षरacters(काष्ठा tty3270 *tp, पूर्णांक n)
अणु
	काष्ठा tty3270_line *line;
	काष्ठा tty3270_cell *cell;

	line = tp->screen + tp->cy;
	जबतक (line->len > tp->cx && n-- > 0) अणु
		cell = line->cells + tp->cx++;
		cell->अक्षरacter = ' ';
		cell->highlight = TAX_RESET;
		cell->f_color = TAC_RESET;
	पूर्ण
	tp->cx += n;
	tp->cx = min_t(पूर्णांक, tp->cx, tp->view.cols - 1);
पूर्ण

/*
 * Erase line, 3 dअगरferent हालs:
 *  Esc [ 0 K	Erase from current position to end of line inclusive
 *  Esc [ 1 K	Erase from beginning of line to current position inclusive
 *  Esc [ 2 K	Erase entire line (without moving cursor)
 */
अटल व्योम
tty3270_erase_line(काष्ठा tty3270 *tp, पूर्णांक mode)
अणु
	काष्ठा tty3270_line *line;
	काष्ठा tty3270_cell *cell;
	पूर्णांक i;

	line = tp->screen + tp->cy;
	अगर (mode == 0)
		line->len = tp->cx;
	अन्यथा अगर (mode == 1) अणु
		क्रम (i = 0; i < tp->cx; i++) अणु
			cell = line->cells + i;
			cell->अक्षरacter = ' ';
			cell->highlight = TAX_RESET;
			cell->f_color = TAC_RESET;
		पूर्ण
		अगर (line->len <= tp->cx)
			line->len = tp->cx + 1;
	पूर्ण अन्यथा अगर (mode == 2)
		line->len = 0;
	tty3270_convert_line(tp, tp->cy);
पूर्ण

/*
 * Erase display, 3 dअगरferent हालs:
 *  Esc [ 0 J	Erase from current position to bottom of screen inclusive
 *  Esc [ 1 J	Erase from top of screen to current position inclusive
 *  Esc [ 2 J	Erase entire screen (without moving the cursor)
 */
अटल व्योम
tty3270_erase_display(काष्ठा tty3270 *tp, पूर्णांक mode)
अणु
	पूर्णांक i;

	अगर (mode == 0) अणु
		tty3270_erase_line(tp, 0);
		क्रम (i = tp->cy + 1; i < tp->view.rows - 2; i++) अणु
			tp->screen[i].len = 0;
			tty3270_convert_line(tp, i);
		पूर्ण
	पूर्ण अन्यथा अगर (mode == 1) अणु
		क्रम (i = 0; i < tp->cy; i++) अणु
			tp->screen[i].len = 0;
			tty3270_convert_line(tp, i);
		पूर्ण
		tty3270_erase_line(tp, 1);
	पूर्ण अन्यथा अगर (mode == 2) अणु
		क्रम (i = 0; i < tp->view.rows - 2; i++) अणु
			tp->screen[i].len = 0;
			tty3270_convert_line(tp, i);
		पूर्ण
	पूर्ण
	tty3270_rebuild_update(tp);
पूर्ण

/*
 * Set attributes found in an escape sequence.
 *  Esc [ <attr> ; <attr> ; ... m
 */
अटल व्योम
tty3270_set_attributes(काष्ठा tty3270 *tp)
अणु
	अटल अचिन्हित अक्षर f_colors[] = अणु
		TAC_DEFAULT, TAC_RED, TAC_GREEN, TAC_YELLOW, TAC_BLUE,
		TAC_PINK, TAC_TURQ, TAC_WHITE, 0, TAC_DEFAULT
	पूर्ण;
	पूर्णांक i, attr;

	क्रम (i = 0; i <= tp->esc_npar; i++) अणु
		attr = tp->esc_par[i];
		चयन (attr) अणु
		हाल 0:		/* Reset */
			tp->highlight = TAX_RESET;
			tp->f_color = TAC_RESET;
			अवरोध;
		/* Highlight. */
		हाल 4:		/* Start underlining. */
			tp->highlight = TAX_UNDER;
			अवरोध;
		हाल 5:		/* Start blink. */
			tp->highlight = TAX_BLINK;
			अवरोध;
		हाल 7:		/* Start reverse. */
			tp->highlight = TAX_REVER;
			अवरोध;
		हाल 24:	/* End underlining */
			अगर (tp->highlight == TAX_UNDER)
				tp->highlight = TAX_RESET;
			अवरोध;
		हाल 25:	/* End blink. */
			अगर (tp->highlight == TAX_BLINK)
				tp->highlight = TAX_RESET;
			अवरोध;
		हाल 27:	/* End reverse. */
			अगर (tp->highlight == TAX_REVER)
				tp->highlight = TAX_RESET;
			अवरोध;
		/* Foreground color. */
		हाल 30:	/* Black */
		हाल 31:	/* Red */
		हाल 32:	/* Green */
		हाल 33:	/* Yellow */
		हाल 34:	/* Blue */
		हाल 35:	/* Magenta */
		हाल 36:	/* Cyan */
		हाल 37:	/* White */
		हाल 39:	/* Black */
			tp->f_color = f_colors[attr - 30];
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
tty3270_getpar(काष्ठा tty3270 *tp, पूर्णांक ix)
अणु
	वापस (tp->esc_par[ix] > 0) ? tp->esc_par[ix] : 1;
पूर्ण

अटल व्योम
tty3270_जाओ_xy(काष्ठा tty3270 *tp, पूर्णांक cx, पूर्णांक cy)
अणु
	पूर्णांक max_cx = max(0, cx);
	पूर्णांक max_cy = max(0, cy);

	tp->cx = min_t(पूर्णांक, tp->view.cols - 1, max_cx);
	cy = min_t(पूर्णांक, tp->view.rows - 3, max_cy);
	अगर (cy != tp->cy) अणु
		tty3270_convert_line(tp, tp->cy);
		tp->cy = cy;
	पूर्ण
पूर्ण

/*
 * Process escape sequences. Known sequences:
 *  Esc 7			Save Cursor Position
 *  Esc 8			Restore Cursor Position
 *  Esc [ Pn ; Pn ; .. m	Set attributes
 *  Esc [ Pn ; Pn H		Cursor Position
 *  Esc [ Pn ; Pn f		Cursor Position
 *  Esc [ Pn A			Cursor Up
 *  Esc [ Pn B			Cursor Down
 *  Esc [ Pn C			Cursor Forward
 *  Esc [ Pn D			Cursor Backward
 *  Esc [ Pn G			Cursor Horizontal Absolute
 *  Esc [ Pn X			Erase Characters
 *  Esc [ Ps J			Erase in Display
 *  Esc [ Ps K			Erase in Line
 * // FIXME: add all the new ones.
 *
 *  Pn is a numeric parameter, a string of zero or more decimal digits.
 *  Ps is a selective parameter.
 */
अटल व्योम
tty3270_escape_sequence(काष्ठा tty3270 *tp, अक्षर ch)
अणु
	क्रमागत अणु ESnormal, ESesc, ESsquare, ESgetpars पूर्ण;

	अगर (tp->esc_state == ESnormal) अणु
		अगर (ch == 0x1b)
			/* Starting new escape sequence. */
			tp->esc_state = ESesc;
		वापस;
	पूर्ण
	अगर (tp->esc_state == ESesc) अणु
		tp->esc_state = ESnormal;
		चयन (ch) अणु
		हाल '[':
			tp->esc_state = ESsquare;
			अवरोध;
		हाल 'E':
			tty3270_cr(tp);
			tty3270_lf(tp);
			अवरोध;
		हाल 'M':
			tty3270_ri(tp);
			अवरोध;
		हाल 'D':
			tty3270_lf(tp);
			अवरोध;
		हाल 'Z':		/* Respond ID. */
			kbd_माला_दो_queue(&tp->port, "\033[?6c");
			अवरोध;
		हाल '7':		/* Save cursor position. */
			tp->saved_cx = tp->cx;
			tp->saved_cy = tp->cy;
			tp->saved_highlight = tp->highlight;
			tp->saved_f_color = tp->f_color;
			अवरोध;
		हाल '8':		/* Restore cursor position. */
			tty3270_convert_line(tp, tp->cy);
			tty3270_जाओ_xy(tp, tp->saved_cx, tp->saved_cy);
			tp->highlight = tp->saved_highlight;
			tp->f_color = tp->saved_f_color;
			अवरोध;
		हाल 'c':		/* Reset terminal. */
			tp->cx = tp->saved_cx = 0;
			tp->cy = tp->saved_cy = 0;
			tp->highlight = tp->saved_highlight = TAX_RESET;
			tp->f_color = tp->saved_f_color = TAC_RESET;
			tty3270_erase_display(tp, 2);
			अवरोध;
		पूर्ण
		वापस;
	पूर्ण
	अगर (tp->esc_state == ESsquare) अणु
		tp->esc_state = ESgetpars;
		स_रखो(tp->esc_par, 0, माप(tp->esc_par));
		tp->esc_npar = 0;
		tp->esc_ques = (ch == '?');
		अगर (tp->esc_ques)
			वापस;
	पूर्ण
	अगर (tp->esc_state == ESgetpars) अणु
		अगर (ch == ';' && tp->esc_npar < ESCAPE_NPAR - 1) अणु
			tp->esc_npar++;
			वापस;
		पूर्ण
		अगर (ch >= '0' && ch <= '9') अणु
			tp->esc_par[tp->esc_npar] *= 10;
			tp->esc_par[tp->esc_npar] += ch - '0';
			वापस;
		पूर्ण
	पूर्ण
	tp->esc_state = ESnormal;
	अगर (ch == 'n' && !tp->esc_ques) अणु
		अगर (tp->esc_par[0] == 5)		/* Status report. */
			kbd_माला_दो_queue(&tp->port, "\033[0n");
		अन्यथा अगर (tp->esc_par[0] == 6) अणु	/* Cursor report. */
			अक्षर buf[40];
			प्र_लिखो(buf, "\033[%d;%dR", tp->cy + 1, tp->cx + 1);
			kbd_माला_दो_queue(&tp->port, buf);
		पूर्ण
		वापस;
	पूर्ण
	अगर (tp->esc_ques)
		वापस;
	चयन (ch) अणु
	हाल 'm':
		tty3270_set_attributes(tp);
		अवरोध;
	हाल 'H':	/* Set cursor position. */
	हाल 'f':
		tty3270_जाओ_xy(tp, tty3270_getpar(tp, 1) - 1,
				tty3270_getpar(tp, 0) - 1);
		अवरोध;
	हाल 'd':	/* Set y position. */
		tty3270_जाओ_xy(tp, tp->cx, tty3270_getpar(tp, 0) - 1);
		अवरोध;
	हाल 'A':	/* Cursor up. */
	हाल 'F':
		tty3270_जाओ_xy(tp, tp->cx, tp->cy - tty3270_getpar(tp, 0));
		अवरोध;
	हाल 'B':	/* Cursor करोwn. */
	हाल 'e':
	हाल 'E':
		tty3270_जाओ_xy(tp, tp->cx, tp->cy + tty3270_getpar(tp, 0));
		अवरोध;
	हाल 'C':	/* Cursor क्रमward. */
	हाल 'a':
		tty3270_जाओ_xy(tp, tp->cx + tty3270_getpar(tp, 0), tp->cy);
		अवरोध;
	हाल 'D':	/* Cursor backward. */
		tty3270_जाओ_xy(tp, tp->cx - tty3270_getpar(tp, 0), tp->cy);
		अवरोध;
	हाल 'G':	/* Set x position. */
	हाल '`':
		tty3270_जाओ_xy(tp, tty3270_getpar(tp, 0), tp->cy);
		अवरोध;
	हाल 'X':	/* Erase Characters. */
		tty3270_erase_अक्षरacters(tp, tty3270_getpar(tp, 0));
		अवरोध;
	हाल 'J':	/* Erase display. */
		tty3270_erase_display(tp, tp->esc_par[0]);
		अवरोध;
	हाल 'K':	/* Erase line. */
		tty3270_erase_line(tp, tp->esc_par[0]);
		अवरोध;
	हाल 'P':	/* Delete अक्षरacters. */
		tty3270_delete_अक्षरacters(tp, tty3270_getpar(tp, 0));
		अवरोध;
	हाल '@':	/* Insert अक्षरacters. */
		tty3270_insert_अक्षरacters(tp, tty3270_getpar(tp, 0));
		अवरोध;
	हाल 's':	/* Save cursor position. */
		tp->saved_cx = tp->cx;
		tp->saved_cy = tp->cy;
		tp->saved_highlight = tp->highlight;
		tp->saved_f_color = tp->f_color;
		अवरोध;
	हाल 'u':	/* Restore cursor position. */
		tty3270_convert_line(tp, tp->cy);
		tty3270_जाओ_xy(tp, tp->saved_cx, tp->saved_cy);
		tp->highlight = tp->saved_highlight;
		tp->f_color = tp->saved_f_color;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * String ग_लिखो routine क्रम 3270 ttys
 */
अटल व्योम
tty3270_करो_ग_लिखो(काष्ठा tty3270 *tp, काष्ठा tty_काष्ठा *tty,
		स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i_msg, i;

	spin_lock_bh(&tp->view.lock);
	क्रम (i_msg = 0; !tty->stopped && i_msg < count; i_msg++) अणु
		अगर (tp->esc_state != 0) अणु
			/* Continue escape sequence. */
			tty3270_escape_sequence(tp, buf[i_msg]);
			जारी;
		पूर्ण

		चयन (buf[i_msg]) अणु
		हाल 0x07:		/* '\a' -- Alarm */
			tp->wcc |= TW_PLUSALARM;
			अवरोध;
		हाल 0x08:		/* Backspace. */
			अगर (tp->cx > 0) अणु
				tp->cx--;
				tty3270_put_अक्षरacter(tp, ' ');
			पूर्ण
			अवरोध;
		हाल 0x09:		/* '\t' -- Tabulate */
			क्रम (i = tp->cx % 8; i < 8; i++) अणु
				अगर (tp->cx >= tp->view.cols) अणु
					tty3270_cr(tp);
					tty3270_lf(tp);
					अवरोध;
				पूर्ण
				tty3270_put_अक्षरacter(tp, ' ');
				tp->cx++;
			पूर्ण
			अवरोध;
		हाल 0x0a:		/* '\n' -- New Line */
			tty3270_cr(tp);
			tty3270_lf(tp);
			अवरोध;
		हाल 0x0c:		/* '\f' -- Form Feed */
			tty3270_erase_display(tp, 2);
			tp->cx = tp->cy = 0;
			अवरोध;
		हाल 0x0d:		/* '\r' -- Carriage Return */
			tp->cx = 0;
			अवरोध;
		हाल 0x0f:		/* SuSE "exit alternate mode" */
			अवरोध;
		हाल 0x1b:		/* Start escape sequence. */
			tty3270_escape_sequence(tp, buf[i_msg]);
			अवरोध;
		शेष:		/* Insert normal अक्षरacter. */
			अगर (tp->cx >= tp->view.cols) अणु
				tty3270_cr(tp);
				tty3270_lf(tp);
			पूर्ण
			tty3270_put_अक्षरacter(tp, buf[i_msg]);
			tp->cx++;
			अवरोध;
		पूर्ण
	पूर्ण
	/* Convert current line to 3270 data fragment. */
	tty3270_convert_line(tp, tp->cy);

	/* Setup समयr to update display after 1/10 second */
	अगर (!समयr_pending(&tp->समयr))
		tty3270_set_समयr(tp, HZ/10);

	spin_unlock_bh(&tp->view.lock);
पूर्ण

/*
 * String ग_लिखो routine क्रम 3270 ttys
 */
अटल पूर्णांक
tty3270_ग_लिखो(काष्ठा tty_काष्ठा * tty,
	      स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा tty3270 *tp;

	tp = tty->driver_data;
	अगर (!tp)
		वापस 0;
	अगर (tp->अक्षर_count > 0) अणु
		tty3270_करो_ग_लिखो(tp, tty, tp->अक्षर_buf, tp->अक्षर_count);
		tp->अक्षर_count = 0;
	पूर्ण
	tty3270_करो_ग_लिखो(tp, tty, buf, count);
	वापस count;
पूर्ण

/*
 * Put single अक्षरacters to the ttys अक्षरacter buffer
 */
अटल पूर्णांक tty3270_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	काष्ठा tty3270 *tp;

	tp = tty->driver_data;
	अगर (!tp || tp->अक्षर_count >= TTY3270_CHAR_BUF_SIZE)
		वापस 0;
	tp->अक्षर_buf[tp->अक्षर_count++] = ch;
	वापस 1;
पूर्ण

/*
 * Flush all अक्षरacters from the ttys अक्षरaceter buffer put there
 * by tty3270_put_अक्षर.
 */
अटल व्योम
tty3270_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty3270 *tp;

	tp = tty->driver_data;
	अगर (!tp)
		वापस;
	अगर (tp->अक्षर_count > 0) अणु
		tty3270_करो_ग_लिखो(tp, tty, tp->अक्षर_buf, tp->अक्षर_count);
		tp->अक्षर_count = 0;
	पूर्ण
पूर्ण

/*
 * Returns the number of अक्षरacters in the output buffer. This is
 * used in tty_रुको_until_sent to रुको until all अक्षरacters have
 * appeared on the screen.
 */
अटल पूर्णांक
tty3270_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 0;
पूर्ण

अटल व्योम
tty3270_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
पूर्ण

/*
 * Check क्रम visible/invisible input चयनes
 */
अटल व्योम
tty3270_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	काष्ठा tty3270 *tp;
	पूर्णांक new;

	tp = tty->driver_data;
	अगर (!tp)
		वापस;
	spin_lock_bh(&tp->view.lock);
	अगर (L_ICANON(tty)) अणु
		new = L_ECHO(tty) ? TF_INPUT: TF_INPUTN;
		अगर (new != tp->inattr) अणु
			tp->inattr = new;
			tty3270_update_prompt(tp, शून्य, 0);
			tty3270_set_समयr(tp, 1);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&tp->view.lock);
पूर्ण

/*
 * Disable पढ़ोing from a 3270 tty
 */
अटल व्योम
tty3270_throttle(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा tty3270 *tp;

	tp = tty->driver_data;
	अगर (!tp)
		वापस;
	tp->throttle = 1;
पूर्ण

/*
 * Enable पढ़ोing from a 3270 tty
 */
अटल व्योम
tty3270_unthrottle(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा tty3270 *tp;

	tp = tty->driver_data;
	अगर (!tp)
		वापस;
	tp->throttle = 0;
	अगर (tp->attn)
		tty3270_issue_पढ़ो(tp, 1);
पूर्ण

/*
 * Hang up the tty device.
 */
अटल व्योम
tty3270_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty3270 *tp;

	tp = tty->driver_data;
	अगर (!tp)
		वापस;
	spin_lock_bh(&tp->view.lock);
	tp->cx = tp->saved_cx = 0;
	tp->cy = tp->saved_cy = 0;
	tp->highlight = tp->saved_highlight = TAX_RESET;
	tp->f_color = tp->saved_f_color = TAC_RESET;
	tty3270_blank_screen(tp);
	जबतक (tp->nr_lines < tp->view.rows - 2)
		tty3270_blank_line(tp);
	tp->update_flags = TTY_UPDATE_ALL;
	spin_unlock_bh(&tp->view.lock);
	tty3270_set_समयr(tp, 1);
पूर्ण

अटल व्योम
tty3270_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
पूर्ण

अटल पूर्णांक tty3270_ioctl(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	काष्ठा tty3270 *tp;

	tp = tty->driver_data;
	अगर (!tp)
		वापस -ENODEV;
	अगर (tty_io_error(tty))
		वापस -EIO;
	वापस kbd_ioctl(tp->kbd, cmd, arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ tty3270_compat_ioctl(काष्ठा tty_काष्ठा *tty,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tty3270 *tp;

	tp = tty->driver_data;
	अगर (!tp)
		वापस -ENODEV;
	अगर (tty_io_error(tty))
		वापस -EIO;
	वापस kbd_ioctl(tp->kbd, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा tty_operations tty3270_ops = अणु
	.install = tty3270_install,
	.cleanup = tty3270_cleanup,
	.खोलो = tty3270_खोलो,
	.बंद = tty3270_बंद,
	.ग_लिखो = tty3270_ग_लिखो,
	.put_अक्षर = tty3270_put_अक्षर,
	.flush_अक्षरs = tty3270_flush_अक्षरs,
	.ग_लिखो_room = tty3270_ग_लिखो_room,
	.अक्षरs_in_buffer = tty3270_अक्षरs_in_buffer,
	.flush_buffer = tty3270_flush_buffer,
	.throttle = tty3270_throttle,
	.unthrottle = tty3270_unthrottle,
	.hangup = tty3270_hangup,
	.रुको_until_sent = tty3270_रुको_until_sent,
	.ioctl = tty3270_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = tty3270_compat_ioctl,
#पूर्ण_अगर
	.set_termios = tty3270_set_termios
पूर्ण;

अटल व्योम tty3270_create_cb(पूर्णांक minor)
अणु
	tty_रेजिस्टर_device(tty3270_driver, minor - RAW3270_FIRSTMINOR, शून्य);
पूर्ण

अटल व्योम tty3270_destroy_cb(पूर्णांक minor)
अणु
	tty_unरेजिस्टर_device(tty3270_driver, minor - RAW3270_FIRSTMINOR);
पूर्ण

अटल काष्ठा raw3270_notअगरier tty3270_notअगरier =
अणु
	.create = tty3270_create_cb,
	.destroy = tty3270_destroy_cb,
पूर्ण;

/*
 * 3270 tty registration code called from tty_init().
 * Most kernel services (incl. kदो_स्मृति) are available at this poimt.
 */
अटल पूर्णांक __init tty3270_init(व्योम)
अणु
	काष्ठा tty_driver *driver;
	पूर्णांक ret;

	driver = tty_alloc_driver(RAW3270_MAXDEVS,
				  TTY_DRIVER_REAL_RAW |
				  TTY_DRIVER_DYNAMIC_DEV |
				  TTY_DRIVER_RESET_TERMIOS);
	अगर (IS_ERR(driver))
		वापस PTR_ERR(driver);

	/*
	 * Initialize the tty_driver काष्ठाure
	 * Entries in tty3270_driver that are NOT initialized:
	 * proc_entry, set_termios, flush_buffer, set_ldisc, ग_लिखो_proc
	 */
	driver->driver_name = "tty3270";
	driver->name = "3270/tty";
	driver->major = IBM_TTY3270_MAJOR;
	driver->minor_start = RAW3270_FIRSTMINOR;
	driver->name_base = RAW3270_FIRSTMINOR;
	driver->type = TTY_DRIVER_TYPE_SYSTEM;
	driver->subtype = SYSTEM_TYPE_TTY;
	driver->init_termios = tty_std_termios;
	tty_set_operations(driver, &tty3270_ops);
	ret = tty_रेजिस्टर_driver(driver);
	अगर (ret) अणु
		put_tty_driver(driver);
		वापस ret;
	पूर्ण
	tty3270_driver = driver;
	raw3270_रेजिस्टर_notअगरier(&tty3270_notअगरier);
	वापस 0;
पूर्ण

अटल व्योम __निकास
tty3270_निकास(व्योम)
अणु
	काष्ठा tty_driver *driver;

	raw3270_unरेजिस्टर_notअगरier(&tty3270_notअगरier);
	driver = tty3270_driver;
	tty3270_driver = शून्य;
	tty_unरेजिस्टर_driver(driver);
	put_tty_driver(driver);
	tty3270_del_views();
पूर्ण

MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(IBM_TTY3270_MAJOR);

module_init(tty3270_init);
module_निकास(tty3270_निकास);
