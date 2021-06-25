<शैली गुरु>
#अगर_अघोषित SRCCODE_H
#घोषणा SRCCODE_H 1

काष्ठा srccode_state अणु
	अक्षर	 *srcfile;
	अचिन्हित line;
पूर्ण;

अटल अंतरभूत व्योम srccode_state_init(काष्ठा srccode_state *state)
अणु
	state->srcfile = शून्य;
	state->line    = 0;
पूर्ण

व्योम srccode_state_मुक्त(काष्ठा srccode_state *state);

/* Result is not 0 terminated */
अक्षर *find_sourceline(अक्षर *fn, अचिन्हित line, पूर्णांक *lenp);

#पूर्ण_अगर
