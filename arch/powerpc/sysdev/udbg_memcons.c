<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A udbg backend which logs messages and पढ़ोs input from in memory
 * buffers.
 *
 * The console output can be पढ़ो from memcons_output which is a
 * circular buffer whose next ग_लिखो position is stored in memcons.output_pos.
 *
 * Input may be passed by writing पूर्णांकo the memcons_input buffer when it is
 * empty. The input buffer is empty when both input_pos == input_start and
 * *input_start == '\0'.
 *
 * Copyright (C) 2003-2005 Anton Blanअक्षरd and Milton Miller, IBM Corp
 * Copyright (C) 2013 Alistair Popple, IBM Corp
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/udbg.h>

काष्ठा memcons अणु
	अक्षर *output_start;
	अक्षर *output_pos;
	अक्षर *output_end;
	अक्षर *input_start;
	अक्षर *input_pos;
	अक्षर *input_end;
पूर्ण;

अटल अक्षर memcons_output[CONFIG_PPC_MEMCONS_OUTPUT_SIZE];
अटल अक्षर memcons_input[CONFIG_PPC_MEMCONS_INPUT_SIZE];

काष्ठा memcons memcons = अणु
	.output_start = memcons_output,
	.output_pos = memcons_output,
	.output_end = &memcons_output[CONFIG_PPC_MEMCONS_OUTPUT_SIZE],
	.input_start = memcons_input,
	.input_pos = memcons_input,
	.input_end = &memcons_input[CONFIG_PPC_MEMCONS_INPUT_SIZE],
पूर्ण;

व्योम memcons_अ_दो(अक्षर c)
अणु
	अक्षर *new_output_pos;

	*memcons.output_pos = c;
	wmb();
	new_output_pos = memcons.output_pos + 1;
	अगर (new_output_pos >= memcons.output_end)
		new_output_pos = memcons.output_start;

	memcons.output_pos = new_output_pos;
पूर्ण

पूर्णांक memcons_अ_लो_poll(व्योम)
अणु
	अक्षर c;
	अक्षर *new_input_pos;

	अगर (*memcons.input_pos) अणु
		c = *memcons.input_pos;

		new_input_pos = memcons.input_pos + 1;
		अगर (new_input_pos >= memcons.input_end)
			new_input_pos = memcons.input_start;
		अन्यथा अगर (*new_input_pos == '\0')
			new_input_pos = memcons.input_start;

		*memcons.input_pos = '\0';
		wmb();
		memcons.input_pos = new_input_pos;
		वापस c;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक memcons_अ_लो(व्योम)
अणु
	पूर्णांक c;

	जबतक (1) अणु
		c = memcons_अ_लो_poll();
		अगर (c == -1)
			cpu_relax();
		अन्यथा
			अवरोध;
	पूर्ण

	वापस c;
पूर्ण

व्योम udbg_init_memcons(व्योम)
अणु
	udbg_अ_दो = memcons_अ_दो;
	udbg_अ_लो = memcons_अ_लो;
	udbg_अ_लो_poll = memcons_अ_लो_poll;
पूर्ण
