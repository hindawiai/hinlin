<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PRINTK_BRAILLE_H
#घोषणा _PRINTK_BRAILLE_H

#अगर_घोषित CONFIG_A11Y_BRAILLE_CONSOLE

अटल अंतरभूत व्योम
braille_set_options(काष्ठा console_cmdline *c, अक्षर *brl_options)
अणु
	c->brl_options = brl_options;
पूर्ण

/*
 * Setup console according to braille options.
 * Return -EINVAL on syntax error, 0 on success (or no braille option was
 * actually given).
 * Modअगरies str to poपूर्णांक to the serial options
 * Sets brl_options to the parsed braille options.
 */
पूर्णांक
_braille_console_setup(अक्षर **str, अक्षर **brl_options);

पूर्णांक
_braille_रेजिस्टर_console(काष्ठा console *console, काष्ठा console_cmdline *c);

पूर्णांक
_braille_unरेजिस्टर_console(काष्ठा console *console);

#अन्यथा

अटल अंतरभूत व्योम
braille_set_options(काष्ठा console_cmdline *c, अक्षर *brl_options)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
_braille_console_setup(अक्षर **str, अक्षर **brl_options)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
_braille_रेजिस्टर_console(काष्ठा console *console, काष्ठा console_cmdline *c)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
_braille_unरेजिस्टर_console(काष्ठा console *console)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
