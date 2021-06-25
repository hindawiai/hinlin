<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    ebcdic keycode functions क्रम s390 console drivers
 *
 *  S390 version
 *    Copyright IBM Corp. 2003
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 */

#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/sysrq.h>

#समावेश <linux/consolemap.h>
#समावेश <linux/kbd_kern.h>
#समावेश <linux/kbd_diacr.h>
#समावेश <linux/uaccess.h>

#समावेश "keyboard.h"

/*
 * Handler Tables.
 */
#घोषणा K_HANDLERS\
	k_self,		k_fn,		k_spec,		k_ignore,\
	k_dead,		k_ignore,	k_ignore,	k_ignore,\
	k_ignore,	k_ignore,	k_ignore,	k_ignore,\
	k_ignore,	k_ignore,	k_ignore,	k_ignore

प्रकार व्योम (k_handler_fn)(काष्ठा kbd_data *, अचिन्हित अक्षर);
अटल k_handler_fn K_HANDLERS;
अटल k_handler_fn *k_handler[16] = अणु K_HANDLERS पूर्ण;

/* maximum values each key_handler can handle */
अटल स्थिर पूर्णांक kbd_max_vals[] = अणु
	255, ARRAY_SIZE(func_table) - 1, NR_FN_HANDLER - 1, 0,
	NR_DEAD - 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;
अटल स्थिर पूर्णांक KBD_NR_TYPES = ARRAY_SIZE(kbd_max_vals);

अटल स्थिर अचिन्हित अक्षर ret_diacr[NR_DEAD] = अणु
	'`',	/* dead_grave */
	'\'',	/* dead_acute */
	'^',	/* dead_circumflex */
	'~',	/* dead_tilda */
	'"',	/* dead_diaeresis */
	',',	/* dead_cedilla */
	'_',	/* dead_macron */
	'U',	/* dead_breve */
	'.',	/* dead_aboveकरोt */
	'*',	/* dead_abovering */
	'=',	/* dead_द्विगुनacute */
	'c',	/* dead_caron */
	'k',	/* dead_ogonek */
	'i',	/* dead_iota */
	'#',	/* dead_voiced_sound */
	'o',	/* dead_semivoiced_sound */
	'!',	/* dead_belowकरोt */
	'?',	/* dead_hook */
	'+',	/* dead_horn */
	'-',	/* dead_stroke */
	')',	/* dead_abovecomma */
	'(',	/* dead_abovereversedcomma */
	':',	/* dead_द्विगुनgrave */
	'n',	/* dead_invertedbreve */
	';',	/* dead_belowcomma */
	'$',	/* dead_currency */
	'@',	/* dead_greek */
पूर्ण;

/*
 * Alloc/मुक्त of kbd_data काष्ठाures.
 */
काष्ठा kbd_data *
kbd_alloc(व्योम) अणु
	काष्ठा kbd_data *kbd;
	पूर्णांक i;

	kbd = kzalloc(माप(काष्ठा kbd_data), GFP_KERNEL);
	अगर (!kbd)
		जाओ out;
	kbd->key_maps = kzalloc(माप(ebc_key_maps), GFP_KERNEL);
	अगर (!kbd->key_maps)
		जाओ out_kbd;
	क्रम (i = 0; i < ARRAY_SIZE(ebc_key_maps); i++) अणु
		अगर (ebc_key_maps[i]) अणु
			kbd->key_maps[i] = kmemdup(ebc_key_maps[i],
						   माप(u_लघु) * NR_KEYS,
						   GFP_KERNEL);
			अगर (!kbd->key_maps[i])
				जाओ out_maps;
		पूर्ण
	पूर्ण
	kbd->func_table = kzalloc(माप(ebc_func_table), GFP_KERNEL);
	अगर (!kbd->func_table)
		जाओ out_maps;
	क्रम (i = 0; i < ARRAY_SIZE(ebc_func_table); i++) अणु
		अगर (ebc_func_table[i]) अणु
			kbd->func_table[i] = kstrdup(ebc_func_table[i],
						     GFP_KERNEL);
			अगर (!kbd->func_table[i])
				जाओ out_func;
		पूर्ण
	पूर्ण
	kbd->fn_handler =
		kसुस्मृति(NR_FN_HANDLER, माप(fn_handler_fn *), GFP_KERNEL);
	अगर (!kbd->fn_handler)
		जाओ out_func;
	kbd->accent_table = kmemdup(ebc_accent_table,
				    माप(काष्ठा kbdiacruc) * MAX_DIACR,
				    GFP_KERNEL);
	अगर (!kbd->accent_table)
		जाओ out_fn_handler;
	kbd->accent_table_size = ebc_accent_table_size;
	वापस kbd;

out_fn_handler:
	kमुक्त(kbd->fn_handler);
out_func:
	क्रम (i = 0; i < ARRAY_SIZE(ebc_func_table); i++)
		kमुक्त(kbd->func_table[i]);
	kमुक्त(kbd->func_table);
out_maps:
	क्रम (i = 0; i < ARRAY_SIZE(ebc_key_maps); i++)
		kमुक्त(kbd->key_maps[i]);
	kमुक्त(kbd->key_maps);
out_kbd:
	kमुक्त(kbd);
out:
	वापस शून्य;
पूर्ण

व्योम
kbd_मुक्त(काष्ठा kbd_data *kbd)
अणु
	पूर्णांक i;

	kमुक्त(kbd->accent_table);
	kमुक्त(kbd->fn_handler);
	क्रम (i = 0; i < ARRAY_SIZE(ebc_func_table); i++)
		kमुक्त(kbd->func_table[i]);
	kमुक्त(kbd->func_table);
	क्रम (i = 0; i < ARRAY_SIZE(ebc_key_maps); i++)
		kमुक्त(kbd->key_maps[i]);
	kमुक्त(kbd->key_maps);
	kमुक्त(kbd);
पूर्ण

/*
 * Generate ascii -> ebcdic translation table from kbd_data.
 */
व्योम
kbd_ascebc(काष्ठा kbd_data *kbd, अचिन्हित अक्षर *ascebc)
अणु
	अचिन्हित लघु *keymap, keysym;
	पूर्णांक i, j, k;

	स_रखो(ascebc, 0x40, 256);
	क्रम (i = 0; i < ARRAY_SIZE(ebc_key_maps); i++) अणु
		keymap = kbd->key_maps[i];
		अगर (!keymap)
			जारी;
		क्रम (j = 0; j < NR_KEYS; j++) अणु
			k = ((i & 1) << 7) + j;
			keysym = keymap[j];
			अगर (KTYP(keysym) == (KT_LATIN | 0xf0) ||
			    KTYP(keysym) == (KT_LETTER | 0xf0))
				ascebc[KVAL(keysym)] = k;
			अन्यथा अगर (KTYP(keysym) == (KT_DEAD | 0xf0))
				ascebc[ret_diacr[KVAL(keysym)]] = k;
		पूर्ण
	पूर्ण
पूर्ण

#अगर 0
/*
 * Generate ebcdic -> ascii translation table from kbd_data.
 */
व्योम
kbd_ebcasc(काष्ठा kbd_data *kbd, अचिन्हित अक्षर *ebcasc)
अणु
	अचिन्हित लघु *keymap, keysym;
	पूर्णांक i, j, k;

	स_रखो(ebcasc, ' ', 256);
	क्रम (i = 0; i < ARRAY_SIZE(ebc_key_maps); i++) अणु
		keymap = kbd->key_maps[i];
		अगर (!keymap)
			जारी;
		क्रम (j = 0; j < NR_KEYS; j++) अणु
			keysym = keymap[j];
			k = ((i & 1) << 7) + j;
			अगर (KTYP(keysym) == (KT_LATIN | 0xf0) ||
			    KTYP(keysym) == (KT_LETTER | 0xf0))
				ebcasc[k] = KVAL(keysym);
			अन्यथा अगर (KTYP(keysym) == (KT_DEAD | 0xf0))
				ebcasc[k] = ret_diacr[KVAL(keysym)];
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * We have a combining अक्षरacter DIACR here, followed by the अक्षरacter CH.
 * If the combination occurs in the table, वापस the corresponding value.
 * Otherwise, अगर CH is a space or equals DIACR, वापस DIACR.
 * Otherwise, conclude that DIACR was not combining after all,
 * queue it and वापस CH.
 */
अटल अचिन्हित पूर्णांक
handle_diacr(काष्ठा kbd_data *kbd, अचिन्हित पूर्णांक ch)
अणु
	पूर्णांक i, d;

	d = kbd->diacr;
	kbd->diacr = 0;

	क्रम (i = 0; i < kbd->accent_table_size; i++) अणु
		अगर (kbd->accent_table[i].diacr == d &&
		    kbd->accent_table[i].base == ch)
			वापस kbd->accent_table[i].result;
	पूर्ण

	अगर (ch == ' ' || ch == d)
		वापस d;

	kbd_put_queue(kbd->port, d);
	वापस ch;
पूर्ण

/*
 * Handle dead key.
 */
अटल व्योम
k_dead(काष्ठा kbd_data *kbd, अचिन्हित अक्षर value)
अणु
	value = ret_diacr[value];
	kbd->diacr = (kbd->diacr ? handle_diacr(kbd, value) : value);
पूर्ण

/*
 * Normal अक्षरacter handler.
 */
अटल व्योम
k_self(काष्ठा kbd_data *kbd, अचिन्हित अक्षर value)
अणु
	अगर (kbd->diacr)
		value = handle_diacr(kbd, value);
	kbd_put_queue(kbd->port, value);
पूर्ण

/*
 * Special key handlers
 */
अटल व्योम
k_ignore(काष्ठा kbd_data *kbd, अचिन्हित अक्षर value)
अणु
पूर्ण

/*
 * Function key handler.
 */
अटल व्योम
k_fn(काष्ठा kbd_data *kbd, अचिन्हित अक्षर value)
अणु
	अगर (kbd->func_table[value])
		kbd_माला_दो_queue(kbd->port, kbd->func_table[value]);
पूर्ण

अटल व्योम
k_spec(काष्ठा kbd_data *kbd, अचिन्हित अक्षर value)
अणु
	अगर (value >= NR_FN_HANDLER)
		वापस;
	अगर (kbd->fn_handler[value])
		kbd->fn_handler[value](kbd);
पूर्ण

/*
 * Put utf8 अक्षरacter to tty flip buffer.
 * UTF-8 is defined क्रम words of up to 31 bits,
 * but we need only 16 bits here
 */
अटल व्योम
to_utf8(काष्ठा tty_port *port, uलघु c)
अणु
	अगर (c < 0x80)
		/*  0******* */
		kbd_put_queue(port, c);
	अन्यथा अगर (c < 0x800) अणु
		/* 110***** 10****** */
		kbd_put_queue(port, 0xc0 | (c >> 6));
		kbd_put_queue(port, 0x80 | (c & 0x3f));
	पूर्ण अन्यथा अणु
		/* 1110**** 10****** 10****** */
		kbd_put_queue(port, 0xe0 | (c >> 12));
		kbd_put_queue(port, 0x80 | ((c >> 6) & 0x3f));
		kbd_put_queue(port, 0x80 | (c & 0x3f));
	पूर्ण
पूर्ण

/*
 * Process keycode.
 */
व्योम
kbd_keycode(काष्ठा kbd_data *kbd, अचिन्हित पूर्णांक keycode)
अणु
	अचिन्हित लघु keysym;
	अचिन्हित अक्षर type, value;

	अगर (!kbd)
		वापस;

	अगर (keycode >= 384)
		keysym = kbd->key_maps[5][keycode - 384];
	अन्यथा अगर (keycode >= 256)
		keysym = kbd->key_maps[4][keycode - 256];
	अन्यथा अगर (keycode >= 128)
		keysym = kbd->key_maps[1][keycode - 128];
	अन्यथा
		keysym = kbd->key_maps[0][keycode];

	type = KTYP(keysym);
	अगर (type >= 0xf0) अणु
		type -= 0xf0;
		अगर (type == KT_LETTER)
			type = KT_LATIN;
		value = KVAL(keysym);
#अगर_घोषित CONFIG_MAGIC_SYSRQ	       /* Handle the SysRq Hack */
		अगर (kbd->sysrq) अणु
			अगर (kbd->sysrq == K(KT_LATIN, '-')) अणु
				kbd->sysrq = 0;
				handle_sysrq(value);
				वापस;
			पूर्ण
			अगर (value == '-') अणु
				kbd->sysrq = K(KT_LATIN, '-');
				वापस;
			पूर्ण
			/* Incomplete sysrq sequence. */
			(*k_handler[KTYP(kbd->sysrq)])(kbd, KVAL(kbd->sysrq));
			kbd->sysrq = 0;
		पूर्ण अन्यथा अगर ((type == KT_LATIN && value == '^') ||
			   (type == KT_DEAD && ret_diacr[value] == '^')) अणु
			kbd->sysrq = K(type, value);
			वापस;
		पूर्ण
#पूर्ण_अगर
		(*k_handler[type])(kbd, value);
	पूर्ण अन्यथा
		to_utf8(kbd->port, keysym);
पूर्ण

/*
 * Ioctl stuff.
 */
अटल पूर्णांक
करो_kdsk_ioctl(काष्ठा kbd_data *kbd, काष्ठा kbentry __user *user_kbe,
	      पूर्णांक cmd, पूर्णांक perm)
अणु
	काष्ठा kbentry पंचांगp;
	अचिन्हित दीर्घ kb_index, kb_table;
	uलघु *key_map, val, ov;

	अगर (copy_from_user(&पंचांगp, user_kbe, माप(काष्ठा kbentry)))
		वापस -EFAULT;
	kb_index = (अचिन्हित दीर्घ) पंचांगp.kb_index;
#अगर NR_KEYS < 256
	अगर (kb_index >= NR_KEYS)
		वापस -EINVAL;
#पूर्ण_अगर
	kb_table = (अचिन्हित दीर्घ) पंचांगp.kb_table;
#अगर MAX_NR_KEYMAPS < 256
	अगर (kb_table >= MAX_NR_KEYMAPS)
		वापस -EINVAL;	
	kb_table = array_index_nospec(kb_table , MAX_NR_KEYMAPS);
#पूर्ण_अगर

	चयन (cmd) अणु
	हाल KDGKBENT:
		key_map = kbd->key_maps[kb_table];
		अगर (key_map) अणु
		    val = U(key_map[kb_index]);
		    अगर (KTYP(val) >= KBD_NR_TYPES)
			val = K_HOLE;
		पूर्ण अन्यथा
		    val = (kb_index ? K_HOLE : K_NOSUCHMAP);
		वापस put_user(val, &user_kbe->kb_value);
	हाल KDSKBENT:
		अगर (!perm)
			वापस -EPERM;
		अगर (!kb_index && पंचांगp.kb_value == K_NOSUCHMAP) अणु
			/* disallocate map */
			key_map = kbd->key_maps[kb_table];
			अगर (key_map) अणु
			    kbd->key_maps[kb_table] = शून्य;
			    kमुक्त(key_map);
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (KTYP(पंचांगp.kb_value) >= KBD_NR_TYPES)
			वापस -EINVAL;
		अगर (KVAL(पंचांगp.kb_value) > kbd_max_vals[KTYP(पंचांगp.kb_value)])
			वापस -EINVAL;

		अगर (!(key_map = kbd->key_maps[kb_table])) अणु
			पूर्णांक j;

			key_map = kदो_स्मृति(माप(plain_map),
						     GFP_KERNEL);
			अगर (!key_map)
				वापस -ENOMEM;
			kbd->key_maps[kb_table] = key_map;
			क्रम (j = 0; j < NR_KEYS; j++)
				key_map[j] = U(K_HOLE);
		पूर्ण
		ov = U(key_map[kb_index]);
		अगर (पंचांगp.kb_value == ov)
			अवरोध;	/* nothing to करो */
		/*
		 * Attention Key.
		 */
		अगर (((ov == K_SAK) || (पंचांगp.kb_value == K_SAK)) &&
		    !capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		key_map[kb_index] = U(पंचांगp.kb_value);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
करो_kdgkb_ioctl(काष्ठा kbd_data *kbd, काष्ठा kbsentry __user *u_kbs,
	       पूर्णांक cmd, पूर्णांक perm)
अणु
	अचिन्हित अक्षर kb_func;
	अक्षर *p;
	पूर्णांक len;

	/* Get u_kbs->kb_func. */
	अगर (get_user(kb_func, &u_kbs->kb_func))
		वापस -EFAULT;
#अगर MAX_NR_FUNC < 256
	अगर (kb_func >= MAX_NR_FUNC)
		वापस -EINVAL;
#पूर्ण_अगर

	चयन (cmd) अणु
	हाल KDGKBSENT:
		p = kbd->func_table[kb_func];
		अगर (p) अणु
			len = म_माप(p);
			अगर (len >= माप(u_kbs->kb_string))
				len = माप(u_kbs->kb_string) - 1;
			अगर (copy_to_user(u_kbs->kb_string, p, len))
				वापस -EFAULT;
		पूर्ण अन्यथा
			len = 0;
		अगर (put_user('\0', u_kbs->kb_string + len))
			वापस -EFAULT;
		अवरोध;
	हाल KDSKBSENT:
		अगर (!perm)
			वापस -EPERM;
		p = strndup_user(u_kbs->kb_string, माप(u_kbs->kb_string));
		अगर (IS_ERR(p))
			वापस PTR_ERR(p);
		kमुक्त(kbd->func_table[kb_func]);
		kbd->func_table[kb_func] = p;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक kbd_ioctl(काष्ठा kbd_data *kbd, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tty_काष्ठा *tty;
	व्योम __user *argp;
	अचिन्हित पूर्णांक ct;
	पूर्णांक perm;

	argp = (व्योम __user *)arg;

	/*
	 * To have permissions to करो most of the vt ioctls, we either have
	 * to be the owner of the tty, or have CAP_SYS_TTY_CONFIG.
	 */
	tty = tty_port_tty_get(kbd->port);
	/* FIXME this test is pretty racy */
	perm = current->संकेत->tty == tty || capable(CAP_SYS_TTY_CONFIG);
	tty_kref_put(tty);
	चयन (cmd) अणु
	हाल KDGKBTYPE:
		वापस put_user(KB_101, (अक्षर __user *)argp);
	हाल KDGKBENT:
	हाल KDSKBENT:
		वापस करो_kdsk_ioctl(kbd, argp, cmd, perm);
	हाल KDGKBSENT:
	हाल KDSKBSENT:
		वापस करो_kdgkb_ioctl(kbd, argp, cmd, perm);
	हाल KDGKBDIACR:
	अणु
		काष्ठा kbdiacrs __user *a = argp;
		काष्ठा kbdiacr diacr;
		पूर्णांक i;

		अगर (put_user(kbd->accent_table_size, &a->kb_cnt))
			वापस -EFAULT;
		क्रम (i = 0; i < kbd->accent_table_size; i++) अणु
			diacr.diacr = kbd->accent_table[i].diacr;
			diacr.base = kbd->accent_table[i].base;
			diacr.result = kbd->accent_table[i].result;
			अगर (copy_to_user(a->kbdiacr + i, &diacr, माप(काष्ठा kbdiacr)))
			वापस -EFAULT;
		पूर्ण
		वापस 0;
	पूर्ण
	हाल KDGKBDIACRUC:
	अणु
		काष्ठा kbdiacrsuc __user *a = argp;

		ct = kbd->accent_table_size;
		अगर (put_user(ct, &a->kb_cnt))
			वापस -EFAULT;
		अगर (copy_to_user(a->kbdiacruc, kbd->accent_table,
				 ct * माप(काष्ठा kbdiacruc)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल KDSKBDIACR:
	अणु
		काष्ठा kbdiacrs __user *a = argp;
		काष्ठा kbdiacr diacr;
		पूर्णांक i;

		अगर (!perm)
			वापस -EPERM;
		अगर (get_user(ct, &a->kb_cnt))
			वापस -EFAULT;
		अगर (ct >= MAX_DIACR)
			वापस -EINVAL;
		kbd->accent_table_size = ct;
		क्रम (i = 0; i < ct; i++) अणु
			अगर (copy_from_user(&diacr, a->kbdiacr + i, माप(काष्ठा kbdiacr)))
				वापस -EFAULT;
			kbd->accent_table[i].diacr = diacr.diacr;
			kbd->accent_table[i].base = diacr.base;
			kbd->accent_table[i].result = diacr.result;
		पूर्ण
		वापस 0;
	पूर्ण
	हाल KDSKBDIACRUC:
	अणु
		काष्ठा kbdiacrsuc __user *a = argp;

		अगर (!perm)
			वापस -EPERM;
		अगर (get_user(ct, &a->kb_cnt))
			वापस -EFAULT;
		अगर (ct >= MAX_DIACR)
			वापस -EINVAL;
		kbd->accent_table_size = ct;
		अगर (copy_from_user(kbd->accent_table, a->kbdiacruc,
				   ct * माप(काष्ठा kbdiacruc)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(kbd_ioctl);
EXPORT_SYMBOL(kbd_ascebc);
EXPORT_SYMBOL(kbd_मुक्त);
EXPORT_SYMBOL(kbd_alloc);
EXPORT_SYMBOL(kbd_keycode);
