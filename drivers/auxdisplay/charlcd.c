<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Character LCD driver क्रम Linux
 *
 * Copyright (C) 2000-2008, Willy Tarreau <w@1wt.eu>
 * Copyright (C) 2016-2017 Glider bvba
 */

#समावेश <linux/atomic.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>

#समावेश <generated/utsrelease.h>

#समावेश "charlcd.h"

/* Keep the backlight on this many seconds क्रम each flash */
#घोषणा LCD_BL_TEMPO_PERIOD	4

#घोषणा LCD_ESCAPE_LEN		24	/* Max अक्षरs क्रम LCD escape command */
#घोषणा LCD_ESCAPE_CHAR		27	/* Use अक्षर 27 क्रम escape command */

काष्ठा अक्षरlcd_priv अणु
	काष्ठा अक्षरlcd lcd;

	काष्ठा delayed_work bl_work;
	काष्ठा mutex bl_tempo_lock;	/* Protects access to bl_tempo */
	bool bl_tempo;

	bool must_clear;

	/* contains the LCD config state */
	अचिन्हित दीर्घ पूर्णांक flags;

	/* Current escape sequence and it's length or -1 अगर outside */
	काष्ठा अणु
		अक्षर buf[LCD_ESCAPE_LEN + 1];
		पूर्णांक len;
	पूर्ण esc_seq;

	अचिन्हित दीर्घ दीर्घ drvdata[];
पूर्ण;

#घोषणा अक्षरlcd_to_priv(p)	container_of(p, काष्ठा अक्षरlcd_priv, lcd)

/* Device single-खोलो policy control */
अटल atomic_t अक्षरlcd_available = ATOMIC_INIT(1);

/* turn the backlight on or off */
व्योम अक्षरlcd_backlight(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा अक्षरlcd_priv *priv = अक्षरlcd_to_priv(lcd);

	अगर (!lcd->ops->backlight)
		वापस;

	mutex_lock(&priv->bl_tempo_lock);
	अगर (!priv->bl_tempo)
		lcd->ops->backlight(lcd, on);
	mutex_unlock(&priv->bl_tempo_lock);
पूर्ण
EXPORT_SYMBOL_GPL(अक्षरlcd_backlight);

अटल व्योम अक्षरlcd_bl_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा अक्षरlcd_priv *priv =
		container_of(dwork, काष्ठा अक्षरlcd_priv, bl_work);

	mutex_lock(&priv->bl_tempo_lock);
	अगर (priv->bl_tempo) अणु
		priv->bl_tempo = false;
		अगर (!(priv->flags & LCD_FLAG_L))
			priv->lcd.ops->backlight(&priv->lcd, CHARLCD_OFF);
	पूर्ण
	mutex_unlock(&priv->bl_tempo_lock);
पूर्ण

/* turn the backlight on क्रम a little जबतक */
व्योम अक्षरlcd_poke(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा अक्षरlcd_priv *priv = अक्षरlcd_to_priv(lcd);

	अगर (!lcd->ops->backlight)
		वापस;

	cancel_delayed_work_sync(&priv->bl_work);

	mutex_lock(&priv->bl_tempo_lock);
	अगर (!priv->bl_tempo && !(priv->flags & LCD_FLAG_L))
		lcd->ops->backlight(lcd, CHARLCD_ON);
	priv->bl_tempo = true;
	schedule_delayed_work(&priv->bl_work, LCD_BL_TEMPO_PERIOD * HZ);
	mutex_unlock(&priv->bl_tempo_lock);
पूर्ण
EXPORT_SYMBOL_GPL(अक्षरlcd_poke);

अटल व्योम अक्षरlcd_home(काष्ठा अक्षरlcd *lcd)
अणु
	lcd->addr.x = 0;
	lcd->addr.y = 0;
	lcd->ops->home(lcd);
पूर्ण

अटल व्योम अक्षरlcd_prपूर्णांक(काष्ठा अक्षरlcd *lcd, अक्षर c)
अणु
	अगर (lcd->addr.x >= lcd->width)
		वापस;

	अगर (lcd->अक्षर_conv)
		c = lcd->अक्षर_conv[(अचिन्हित अक्षर)c];

	अगर (!lcd->ops->prपूर्णांक(lcd, c))
		lcd->addr.x++;

	/* prevents the cursor from wrapping onto the next line */
	अगर (lcd->addr.x == lcd->width)
		lcd->ops->जाओxy(lcd, lcd->addr.x - 1, lcd->addr.y);
पूर्ण

अटल व्योम अक्षरlcd_clear_display(काष्ठा अक्षरlcd *lcd)
अणु
	lcd->ops->clear_display(lcd);
	lcd->addr.x = 0;
	lcd->addr.y = 0;
पूर्ण

/*
 * Parses a movement command of the क्रमm "(.*);", where the group can be
 * any number of subcommands of the क्रमm "(x|y)[0-9]+".
 *
 * Returns whether the command is valid. The position arguments are
 * only written अगर the parsing was successful.
 *
 * For instance:
 *   - ";"          वापसs (<original x>, <original y>).
 *   - "x1;"        वापसs (1, <original y>).
 *   - "y2x1;"      वापसs (1, 2).
 *   - "x12y34x56;" वापसs (56, 34).
 *   - ""           fails.
 *   - "x"          fails.
 *   - "x;"         fails.
 *   - "x1"         fails.
 *   - "xy12;"      fails.
 *   - "x12yy12;"   fails.
 *   - "xx"         fails.
 */
अटल bool parse_xy(स्थिर अक्षर *s, अचिन्हित दीर्घ *x, अचिन्हित दीर्घ *y)
अणु
	अचिन्हित दीर्घ new_x = *x;
	अचिन्हित दीर्घ new_y = *y;
	अक्षर *p;

	क्रम (;;) अणु
		अगर (!*s)
			वापस false;

		अगर (*s == ';')
			अवरोध;

		अगर (*s == 'x') अणु
			new_x = simple_म_से_अदीर्घ(s + 1, &p, 10);
			अगर (p == s + 1)
				वापस false;
			s = p;
		पूर्ण अन्यथा अगर (*s == 'y') अणु
			new_y = simple_म_से_अदीर्घ(s + 1, &p, 10);
			अगर (p == s + 1)
				वापस false;
			s = p;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण

	*x = new_x;
	*y = new_y;
	वापस true;
पूर्ण

/*
 * These are the file operation function क्रम user access to /dev/lcd
 * This function can also be called from inside the kernel, by
 * setting file and ppos to शून्य.
 *
 */

अटल अंतरभूत पूर्णांक handle_lcd_special_code(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा अक्षरlcd_priv *priv = अक्षरlcd_to_priv(lcd);

	/* LCD special codes */

	पूर्णांक processed = 0;

	अक्षर *esc = priv->esc_seq.buf + 2;
	पूर्णांक oldflags = priv->flags;

	/* check क्रम display mode flags */
	चयन (*esc) अणु
	हाल 'D':	/* Display ON */
		priv->flags |= LCD_FLAG_D;
		अगर (priv->flags != oldflags)
			lcd->ops->display(lcd, CHARLCD_ON);

		processed = 1;
		अवरोध;
	हाल 'd':	/* Display OFF */
		priv->flags &= ~LCD_FLAG_D;
		अगर (priv->flags != oldflags)
			lcd->ops->display(lcd, CHARLCD_OFF);

		processed = 1;
		अवरोध;
	हाल 'C':	/* Cursor ON */
		priv->flags |= LCD_FLAG_C;
		अगर (priv->flags != oldflags)
			lcd->ops->cursor(lcd, CHARLCD_ON);

		processed = 1;
		अवरोध;
	हाल 'c':	/* Cursor OFF */
		priv->flags &= ~LCD_FLAG_C;
		अगर (priv->flags != oldflags)
			lcd->ops->cursor(lcd, CHARLCD_OFF);

		processed = 1;
		अवरोध;
	हाल 'B':	/* Blink ON */
		priv->flags |= LCD_FLAG_B;
		अगर (priv->flags != oldflags)
			lcd->ops->blink(lcd, CHARLCD_ON);

		processed = 1;
		अवरोध;
	हाल 'b':	/* Blink OFF */
		priv->flags &= ~LCD_FLAG_B;
		अगर (priv->flags != oldflags)
			lcd->ops->blink(lcd, CHARLCD_OFF);

		processed = 1;
		अवरोध;
	हाल '+':	/* Back light ON */
		priv->flags |= LCD_FLAG_L;
		अगर (priv->flags != oldflags)
			अक्षरlcd_backlight(lcd, CHARLCD_ON);

		processed = 1;
		अवरोध;
	हाल '-':	/* Back light OFF */
		priv->flags &= ~LCD_FLAG_L;
		अगर (priv->flags != oldflags)
			अक्षरlcd_backlight(lcd, CHARLCD_OFF);

		processed = 1;
		अवरोध;
	हाल '*':	/* Flash back light */
		अक्षरlcd_poke(lcd);
		processed = 1;
		अवरोध;
	हाल 'f':	/* Small Font */
		priv->flags &= ~LCD_FLAG_F;
		अगर (priv->flags != oldflags)
			lcd->ops->fontsize(lcd, CHARLCD_FONTSIZE_SMALL);

		processed = 1;
		अवरोध;
	हाल 'F':	/* Large Font */
		priv->flags |= LCD_FLAG_F;
		अगर (priv->flags != oldflags)
			lcd->ops->fontsize(lcd, CHARLCD_FONTSIZE_LARGE);

		processed = 1;
		अवरोध;
	हाल 'n':	/* One Line */
		priv->flags &= ~LCD_FLAG_N;
		अगर (priv->flags != oldflags)
			lcd->ops->lines(lcd, CHARLCD_LINES_1);

		processed = 1;
		अवरोध;
	हाल 'N':	/* Two Lines */
		priv->flags |= LCD_FLAG_N;
		अगर (priv->flags != oldflags)
			lcd->ops->lines(lcd, CHARLCD_LINES_2);

		processed = 1;
		अवरोध;
	हाल 'l':	/* Shअगरt Cursor Left */
		अगर (lcd->addr.x > 0) अणु
			अगर (!lcd->ops->shअगरt_cursor(lcd, CHARLCD_SHIFT_LEFT))
				lcd->addr.x--;
		पूर्ण

		processed = 1;
		अवरोध;
	हाल 'r':	/* shअगरt cursor right */
		अगर (lcd->addr.x < lcd->width) अणु
			अगर (!lcd->ops->shअगरt_cursor(lcd, CHARLCD_SHIFT_RIGHT))
				lcd->addr.x++;
		पूर्ण

		processed = 1;
		अवरोध;
	हाल 'L':	/* shअगरt display left */
		lcd->ops->shअगरt_display(lcd, CHARLCD_SHIFT_LEFT);
		processed = 1;
		अवरोध;
	हाल 'R':	/* shअगरt display right */
		lcd->ops->shअगरt_display(lcd, CHARLCD_SHIFT_RIGHT);
		processed = 1;
		अवरोध;
	हाल 'k': अणु	/* समाप्त end of line */
		पूर्णांक x, xs, ys;

		xs = lcd->addr.x;
		ys = lcd->addr.y;
		क्रम (x = lcd->addr.x; x < lcd->width; x++)
			lcd->ops->prपूर्णांक(lcd, ' ');

		/* restore cursor position */
		lcd->addr.x = xs;
		lcd->addr.y = ys;
		lcd->ops->जाओxy(lcd, lcd->addr.x, lcd->addr.y);
		processed = 1;
		अवरोध;
	पूर्ण
	हाल 'I':	/* reinitialize display */
		lcd->ops->init_display(lcd);
		priv->flags = ((lcd->height > 1) ? LCD_FLAG_N : 0) | LCD_FLAG_D |
			LCD_FLAG_C | LCD_FLAG_B;
		processed = 1;
		अवरोध;
	हाल 'G':
		अगर (lcd->ops->redefine_अक्षर)
			processed = lcd->ops->redefine_अक्षर(lcd, esc);
		अन्यथा
			processed = 1;
		अवरोध;

	हाल 'x':	/* जाओxy : LxXXX[yYYY]; */
	हाल 'y':	/* जाओxy : LyYYY[xXXX]; */
		अगर (priv->esc_seq.buf[priv->esc_seq.len - 1] != ';')
			अवरोध;

		/* If the command is valid, move to the new address */
		अगर (parse_xy(esc, &lcd->addr.x, &lcd->addr.y))
			lcd->ops->जाओxy(lcd, lcd->addr.x, lcd->addr.y);

		/* Regardless of its validity, mark as processed */
		processed = 1;
		अवरोध;
	पूर्ण

	वापस processed;
पूर्ण

अटल व्योम अक्षरlcd_ग_लिखो_अक्षर(काष्ठा अक्षरlcd *lcd, अक्षर c)
अणु
	काष्ठा अक्षरlcd_priv *priv = अक्षरlcd_to_priv(lcd);

	/* first, we'll test if we're in escape mode */
	अगर ((c != '\n') && priv->esc_seq.len >= 0) अणु
		/* yes, let's add this अक्षर to the buffer */
		priv->esc_seq.buf[priv->esc_seq.len++] = c;
		priv->esc_seq.buf[priv->esc_seq.len] = '\0';
	पूर्ण अन्यथा अणु
		/* पातs any previous escape sequence */
		priv->esc_seq.len = -1;

		चयन (c) अणु
		हाल LCD_ESCAPE_CHAR:
			/* start of an escape sequence */
			priv->esc_seq.len = 0;
			priv->esc_seq.buf[priv->esc_seq.len] = '\0';
			अवरोध;
		हाल '\b':
			/* go back one अक्षर and clear it */
			अगर (lcd->addr.x > 0) अणु
				/* back one अक्षर */
				अगर (!lcd->ops->shअगरt_cursor(lcd,
							CHARLCD_SHIFT_LEFT))
					lcd->addr.x--;
			पूर्ण
			/* replace with a space */
			अक्षरlcd_prपूर्णांक(lcd, ' ');
			/* back one अक्षर again */
			अगर (!lcd->ops->shअगरt_cursor(lcd, CHARLCD_SHIFT_LEFT))
				lcd->addr.x--;

			अवरोध;
		हाल '\f':
			/* quickly clear the display */
			अक्षरlcd_clear_display(lcd);
			अवरोध;
		हाल '\n':
			/*
			 * flush the reमुख्यder of the current line and
			 * go to the beginning of the next line
			 */
			क्रम (; lcd->addr.x < lcd->width; lcd->addr.x++)
				lcd->ops->prपूर्णांक(lcd, ' ');

			lcd->addr.x = 0;
			lcd->addr.y = (lcd->addr.y + 1) % lcd->height;
			lcd->ops->जाओxy(lcd, lcd->addr.x, lcd->addr.y);
			अवरोध;
		हाल '\r':
			/* go to the beginning of the same line */
			lcd->addr.x = 0;
			lcd->ops->जाओxy(lcd, lcd->addr.x, lcd->addr.y);
			अवरोध;
		हाल '\t':
			/* prपूर्णांक a space instead of the tab */
			अक्षरlcd_prपूर्णांक(lcd, ' ');
			अवरोध;
		शेष:
			/* simply prपूर्णांक this अक्षर */
			अक्षरlcd_prपूर्णांक(lcd, c);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * now we'll see if we're in an escape mode and अगर the current
	 * escape sequence can be understood.
	 */
	अगर (priv->esc_seq.len >= 2) अणु
		पूर्णांक processed = 0;

		अगर (!म_भेद(priv->esc_seq.buf, "[2J")) अणु
			/* clear the display */
			अक्षरlcd_clear_display(lcd);
			processed = 1;
		पूर्ण अन्यथा अगर (!म_भेद(priv->esc_seq.buf, "[H")) अणु
			/* cursor to home */
			अक्षरlcd_home(lcd);
			processed = 1;
		पूर्ण
		/* codes starting with ^[[L */
		अन्यथा अगर ((priv->esc_seq.len >= 3) &&
			 (priv->esc_seq.buf[0] == '[') &&
			 (priv->esc_seq.buf[1] == 'L')) अणु
			processed = handle_lcd_special_code(lcd);
		पूर्ण

		/* LCD special escape codes */
		/*
		 * flush the escape sequence अगर it's been processed
		 * or अगर it is getting too दीर्घ.
		 */
		अगर (processed || (priv->esc_seq.len >= LCD_ESCAPE_LEN))
			priv->esc_seq.len = -1;
	पूर्ण /* escape codes */
पूर्ण

अटल काष्ठा अक्षरlcd *the_अक्षरlcd;

अटल sमाप_प्रकार अक्षरlcd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर __user *पंचांगp = buf;
	अक्षर c;

	क्रम (; count-- > 0; (*ppos)++, पंचांगp++) अणु
		अगर (((count + 1) & 0x1f) == 0) अणु
			/*
			 * अक्षरlcd_ग_लिखो() is invoked as a VFS->ग_लिखो() callback
			 * and as such it is always invoked from preemptible
			 * context and may sleep.
			 */
			cond_resched();
		पूर्ण

		अगर (get_user(c, पंचांगp))
			वापस -EFAULT;

		अक्षरlcd_ग_लिखो_अक्षर(the_अक्षरlcd, c);
	पूर्ण

	वापस पंचांगp - buf;
पूर्ण

अटल पूर्णांक अक्षरlcd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा अक्षरlcd_priv *priv = अक्षरlcd_to_priv(the_अक्षरlcd);
	पूर्णांक ret;

	ret = -EBUSY;
	अगर (!atomic_dec_and_test(&अक्षरlcd_available))
		जाओ fail;	/* खोलो only once at a समय */

	ret = -EPERM;
	अगर (file->f_mode & FMODE_READ)	/* device is ग_लिखो-only */
		जाओ fail;

	अगर (priv->must_clear) अणु
		priv->lcd.ops->clear_display(&priv->lcd);
		priv->must_clear = false;
		priv->lcd.addr.x = 0;
		priv->lcd.addr.y = 0;
	पूर्ण
	वापस nonseekable_खोलो(inode, file);

 fail:
	atomic_inc(&अक्षरlcd_available);
	वापस ret;
पूर्ण

अटल पूर्णांक अक्षरlcd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	atomic_inc(&अक्षरlcd_available);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations अक्षरlcd_fops = अणु
	.ग_लिखो   = अक्षरlcd_ग_लिखो,
	.खोलो    = अक्षरlcd_खोलो,
	.release = अक्षरlcd_release,
	.llseek  = no_llseek,
पूर्ण;

अटल काष्ठा miscdevice अक्षरlcd_dev = अणु
	.minor	= LCD_MINOR,
	.name	= "lcd",
	.fops	= &अक्षरlcd_fops,
पूर्ण;

अटल व्योम अक्षरlcd_माला_दो(काष्ठा अक्षरlcd *lcd, स्थिर अक्षर *s)
अणु
	स्थिर अक्षर *पंचांगp = s;
	पूर्णांक count = म_माप(s);

	क्रम (; count-- > 0; पंचांगp++) अणु
		अगर (((count + 1) & 0x1f) == 0)
			cond_resched();

		अक्षरlcd_ग_लिखो_अक्षर(lcd, *पंचांगp);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PANEL_BOOT_MESSAGE
#घोषणा LCD_INIT_TEXT CONFIG_PANEL_BOOT_MESSAGE
#अन्यथा
#घोषणा LCD_INIT_TEXT "Linux-" UTS_RELEASE "\n"
#पूर्ण_अगर

#अगर_घोषित CONFIG_CHARLCD_BL_ON
#घोषणा LCD_INIT_BL "\x1b[L+"
#या_अगर defined(CONFIG_CHARLCD_BL_FLASH)
#घोषणा LCD_INIT_BL "\x1b[L*"
#अन्यथा
#घोषणा LCD_INIT_BL "\x1b[L-"
#पूर्ण_अगर

/* initialize the LCD driver */
अटल पूर्णांक अक्षरlcd_init(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा अक्षरlcd_priv *priv = अक्षरlcd_to_priv(lcd);
	पूर्णांक ret;

	priv->flags = ((lcd->height > 1) ? LCD_FLAG_N : 0) | LCD_FLAG_D |
		      LCD_FLAG_C | LCD_FLAG_B;
	अगर (lcd->ops->backlight) अणु
		mutex_init(&priv->bl_tempo_lock);
		INIT_DELAYED_WORK(&priv->bl_work, अक्षरlcd_bl_off);
	पूर्ण

	/*
	 * beक्रमe this line, we must NOT send anything to the display.
	 * Since अक्षरlcd_init_display() needs to ग_लिखो data, we have to
	 * enable mark the LCD initialized just beक्रमe.
	 */
	ret = lcd->ops->init_display(lcd);
	अगर (ret)
		वापस ret;

	/* display a लघु message */
	अक्षरlcd_माला_दो(lcd, "\x1b[Lc\x1b[Lb" LCD_INIT_BL LCD_INIT_TEXT);

	/* clear the display on the next device खोलोing */
	priv->must_clear = true;
	अक्षरlcd_home(lcd);
	वापस 0;
पूर्ण

काष्ठा अक्षरlcd *अक्षरlcd_alloc(व्योम)
अणु
	काष्ठा अक्षरlcd_priv *priv;
	काष्ठा अक्षरlcd *lcd;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;

	priv->esc_seq.len = -1;

	lcd = &priv->lcd;

	वापस lcd;
पूर्ण
EXPORT_SYMBOL_GPL(अक्षरlcd_alloc);

व्योम अक्षरlcd_मुक्त(काष्ठा अक्षरlcd *lcd)
अणु
	kमुक्त(अक्षरlcd_to_priv(lcd));
पूर्ण
EXPORT_SYMBOL_GPL(अक्षरlcd_मुक्त);

अटल पूर्णांक panel_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
			    व्योम *unused)
अणु
	काष्ठा अक्षरlcd *lcd = the_अक्षरlcd;

	चयन (code) अणु
	हाल SYS_DOWN:
		अक्षरlcd_माला_दो(lcd,
			     "\x0cReloading\nSystem...\x1b[Lc\x1b[Lb\x1b[L+");
		अवरोध;
	हाल SYS_HALT:
		अक्षरlcd_माला_दो(lcd, "\x0cSystem Halted.\x1b[Lc\x1b[Lb\x1b[L+");
		अवरोध;
	हाल SYS_POWER_OFF:
		अक्षरlcd_माला_दो(lcd, "\x0cPower off.\x1b[Lc\x1b[Lb\x1b[L+");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block panel_notअगरier = अणु
	panel_notअगरy_sys,
	शून्य,
	0
पूर्ण;

पूर्णांक अक्षरlcd_रेजिस्टर(काष्ठा अक्षरlcd *lcd)
अणु
	पूर्णांक ret;

	ret = अक्षरlcd_init(lcd);
	अगर (ret)
		वापस ret;

	ret = misc_रेजिस्टर(&अक्षरlcd_dev);
	अगर (ret)
		वापस ret;

	the_अक्षरlcd = lcd;
	रेजिस्टर_reboot_notअगरier(&panel_notअगरier);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(अक्षरlcd_रेजिस्टर);

पूर्णांक अक्षरlcd_unरेजिस्टर(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा अक्षरlcd_priv *priv = अक्षरlcd_to_priv(lcd);

	unरेजिस्टर_reboot_notअगरier(&panel_notअगरier);
	अक्षरlcd_माला_दो(lcd, "\x0cLCD driver unloaded.\x1b[Lc\x1b[Lb\x1b[L-");
	misc_deरेजिस्टर(&अक्षरlcd_dev);
	the_अक्षरlcd = शून्य;
	अगर (lcd->ops->backlight) अणु
		cancel_delayed_work_sync(&priv->bl_work);
		priv->lcd.ops->backlight(&priv->lcd, CHARLCD_OFF);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(अक्षरlcd_unरेजिस्टर);

MODULE_LICENSE("GPL");
