<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* spk_priv.h
 * review functions क्रम the speakup screen review package.
 * originally written by: Kirk Reiser and Andy Berdan.
 *
 * extensively modअगरied by David Borowski.
 *
 * Copyright (C) 1998  Kirk Reiser.
 * Copyright (C) 2003  David Borowski.
 */
#अगर_अघोषित _SPEAKUP_PRIVATE_H
#घोषणा _SPEAKUP_PRIVATE_H

#समावेश <linux/prपूर्णांकk.h>

#समावेश "spk_types.h"
#समावेश "spk_priv_keyinfo.h"

#घोषणा V_LAST_VAR अणु MAXVARS पूर्ण
#घोषणा SPACE 0x20
#घोषणा SYNTH_CHECK 20030716 /* today's date ought to करो क्रम check value */
/* synth flags, क्रम odd synths */
#घोषणा SF_DEC 1 /* to fiddle puncs in alpha strings so it करोesn't spell */
#अगर_घोषित MODULE
#घोषणा SYNTH_START 1
#अन्यथा
#घोषणा SYNTH_START 0
#पूर्ण_अगर

#घोषणा KT_SPKUP 15
#घोषणा SPK_SYNTH_TIMEOUT 100000 /* in micro-seconds */
#घोषणा SYNTH_DEFAULT_DEV "ttyS0"
#घोषणा SYNTH_DEFAULT_SER 0

स्थिर काष्ठा old_serial_port *spk_serial_init(पूर्णांक index);
व्योम spk_stop_serial_पूर्णांकerrupt(व्योम);
व्योम spk_serial_release(काष्ठा spk_synth *synth);
व्योम spk_ttyio_release(काष्ठा spk_synth *synth);
व्योम spk_ttyio_रेजिस्टर_ldisc(व्योम);
व्योम spk_ttyio_unरेजिस्टर_ldisc(व्योम);

व्योम synth_buffer_skip_nonlatin1(व्योम);
u16 synth_buffer_अ_लो(व्योम);
u16 synth_buffer_peek(व्योम);
पूर्णांक synth_buffer_empty(व्योम);
काष्ठा var_t *spk_get_var(क्रमागत var_id_t var_id);
sमाप_प्रकार spk_var_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		     अक्षर *buf);
sमाप_प्रकार spk_var_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count);

पूर्णांक spk_serial_synth_probe(काष्ठा spk_synth *synth);
पूर्णांक spk_ttyio_synth_probe(काष्ठा spk_synth *synth);
स्थिर अक्षर *spk_serial_synth_immediate(काष्ठा spk_synth *synth,
				       स्थिर अक्षर *buff);
स्थिर अक्षर *spk_ttyio_synth_immediate(काष्ठा spk_synth *synth,
				      स्थिर अक्षर *buff);
व्योम spk_करो_catch_up(काष्ठा spk_synth *synth);
व्योम spk_करो_catch_up_unicode(काष्ठा spk_synth *synth);
व्योम spk_synth_flush(काष्ठा spk_synth *synth);
अचिन्हित अक्षर spk_synth_get_index(काष्ठा spk_synth *synth);
पूर्णांक spk_synth_is_alive_nop(काष्ठा spk_synth *synth);
पूर्णांक spk_synth_is_alive_restart(काष्ठा spk_synth *synth);
__म_लिखो(1, 2)
व्योम synth_म_लिखो(स्थिर अक्षर *buf, ...);
व्योम synth_putwc(u16 wc);
व्योम synth_putwc_s(u16 wc);
व्योम synth_putws(स्थिर u16 *buf);
व्योम synth_putws_s(स्थिर u16 *buf);
पूर्णांक synth_request_region(अचिन्हित दीर्घ start, अचिन्हित दीर्घ n);
पूर्णांक synth_release_region(अचिन्हित दीर्घ start, अचिन्हित दीर्घ n);
पूर्णांक synth_add(काष्ठा spk_synth *in_synth);
व्योम synth_हटाओ(काष्ठा spk_synth *in_synth);
काष्ठा spk_synth *synth_current(व्योम);

बाह्य काष्ठा speakup_info_t speakup_info;

बाह्य काष्ठा var_t synth_समय_vars[];

बाह्य काष्ठा spk_io_ops spk_serial_io_ops;
बाह्य काष्ठा spk_io_ops spk_ttyio_ops;

#पूर्ण_अगर
