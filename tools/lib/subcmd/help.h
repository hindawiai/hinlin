<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SUBCMD_HELP_H
#घोषणा __SUBCMD_HELP_H

#समावेश <sys/types.h>
#समावेश <मानकपन.स>

काष्ठा cmdnames अणु
	माप_प्रकार alloc;
	माप_प्रकार cnt;
	काष्ठा cmdname अणु
		माप_प्रकार len; /* also used क्रम similarity index in help.c */
		अक्षर name[];
	पूर्ण **names;
पूर्ण;

अटल अंतरभूत व्योम mput_अक्षर(अक्षर c, अचिन्हित पूर्णांक num)
अणु
	जबतक(num--)
		अक्षर_दो(c);
पूर्ण

व्योम load_command_list(स्थिर अक्षर *prefix,
		काष्ठा cmdnames *मुख्य_cmds,
		काष्ठा cmdnames *other_cmds);
व्योम add_cmdname(काष्ठा cmdnames *cmds, स्थिर अक्षर *name, माप_प्रकार len);
व्योम clean_cmdnames(काष्ठा cmdnames *cmds);
पूर्णांक cmdname_compare(स्थिर व्योम *a, स्थिर व्योम *b);
व्योम uniq(काष्ठा cmdnames *cmds);
/* Here we require that excludes is a sorted list. */
व्योम exclude_cmds(काष्ठा cmdnames *cmds, काष्ठा cmdnames *excludes);
पूर्णांक is_in_cmdlist(काष्ठा cmdnames *c, स्थिर अक्षर *s);
व्योम list_commands(स्थिर अक्षर *title, काष्ठा cmdnames *मुख्य_cmds,
		   काष्ठा cmdnames *other_cmds);

#पूर्ण_अगर /* __SUBCMD_HELP_H */
