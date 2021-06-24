<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * svghelper.c - helper functions क्रम outputting svg
 *
 * (C) Copyright 2009 Intel Corporation
 *
 * Authors:
 *     Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>
#समावेश <पूर्णांकernal/cpumap.h>
#समावेश <perf/cpumap.h>

#समावेश "env.h"
#समावेश "svghelper.h"

अटल u64 first_समय, last_समय;
अटल u64 turbo_frequency, max_freq;


#घोषणा SLOT_MULT 30.0
#घोषणा SLOT_HEIGHT 25.0
#घोषणा SLOT_HALF (SLOT_HEIGHT / 2)

पूर्णांक svg_page_width = 1000;
u64 svg_highlight;
स्थिर अक्षर *svg_highlight_name;

#घोषणा MIN_TEXT_SIZE 0.01

अटल u64 total_height;
अटल खाता *svgfile;

अटल द्विगुन cpu2slot(पूर्णांक cpu)
अणु
	वापस 2 * cpu + 1;
पूर्ण

अटल पूर्णांक *topology_map;

अटल द्विगुन cpu2y(पूर्णांक cpu)
अणु
	अगर (topology_map)
		वापस cpu2slot(topology_map[cpu]) * SLOT_MULT;
	अन्यथा
		वापस cpu2slot(cpu) * SLOT_MULT;
पूर्ण

अटल द्विगुन समय2pixels(u64 __समय)
अणु
	द्विगुन X;

	X = 1.0 * svg_page_width * (__समय - first_समय) / (last_समय - first_समय);
	वापस X;
पूर्ण

/*
 * Round text sizes so that the svg viewer only needs a discrete
 * number of renderings of the font
 */
अटल द्विगुन round_text_size(द्विगुन size)
अणु
	पूर्णांक loop = 100;
	द्विगुन target = 10.0;

	अगर (size >= 10.0)
		वापस size;
	जबतक (loop--) अणु
		अगर (size >= target)
			वापस target;
		target = target / 2.0;
	पूर्ण
	वापस size;
पूर्ण

व्योम खोलो_svg(स्थिर अक्षर *filename, पूर्णांक cpus, पूर्णांक rows, u64 start, u64 end)
अणु
	पूर्णांक new_width;

	svgfile = ख_खोलो(filename, "w");
	अगर (!svgfile) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot open %s for output\n", filename);
		वापस;
	पूर्ण
	first_समय = start;
	first_समय = first_समय / 100000000 * 100000000;
	last_समय = end;

	/*
	 * अगर the recording is लघु, we शेष to a width of 1000, but
	 * क्रम दीर्घer recordings we want at least 200 units of width per second
	 */
	new_width = (last_समय - first_समय) / 5000000;

	अगर (new_width > svg_page_width)
		svg_page_width = new_width;

	total_height = (1 + rows + cpu2slot(cpus)) * SLOT_MULT;
	ख_लिखो(svgfile, "<?xml version=\"1.0\" standalone=\"no\"?> \n");
	ख_लिखो(svgfile, "<!DOCTYPE svg SYSTEM \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	ख_लिखो(svgfile, "<svg width=\"%i\" height=\"%" PRIu64 "\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n", svg_page_width, total_height);

	ख_लिखो(svgfile, "<defs>\n  <style type=\"text/css\">\n    <![CDATA[\n");

	ख_लिखो(svgfile, "      rect          { stroke-width: 1; }\n");
	ख_लिखो(svgfile, "      rect.process  { fill:rgb(180,180,180); fill-opacity:0.9; stroke-width:1;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.process2 { fill:rgb(180,180,180); fill-opacity:0.9; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.process3 { fill:rgb(180,180,180); fill-opacity:0.5; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.sample   { fill:rgb(  0,  0,255); fill-opacity:0.8; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.sample_hi{ fill:rgb(255,128,  0); fill-opacity:0.8; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.error    { fill:rgb(255,  0,  0); fill-opacity:0.5; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.net      { fill:rgb(  0,128,  0); fill-opacity:0.5; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.disk     { fill:rgb(  0,  0,255); fill-opacity:0.5; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.sync     { fill:rgb(128,128,  0); fill-opacity:0.5; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.poll     { fill:rgb(  0,128,128); fill-opacity:0.2; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.blocked  { fill:rgb(255,  0,  0); fill-opacity:0.5; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.waiting  { fill:rgb(224,214,  0); fill-opacity:0.8; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.WAITING  { fill:rgb(255,214, 48); fill-opacity:0.6; stroke-width:0;   stroke:rgb(  0,  0,  0); } \n");
	ख_लिखो(svgfile, "      rect.cpu      { fill:rgb(192,192,192); fill-opacity:0.2; stroke-width:0.5; stroke:rgb(128,128,128); } \n");
	ख_लिखो(svgfile, "      rect.pstate   { fill:rgb(128,128,128); fill-opacity:0.8; stroke-width:0; } \n");
	ख_लिखो(svgfile, "      rect.c1       { fill:rgb(255,214,214); fill-opacity:0.5; stroke-width:0; } \n");
	ख_लिखो(svgfile, "      rect.c2       { fill:rgb(255,172,172); fill-opacity:0.5; stroke-width:0; } \n");
	ख_लिखो(svgfile, "      rect.c3       { fill:rgb(255,130,130); fill-opacity:0.5; stroke-width:0; } \n");
	ख_लिखो(svgfile, "      rect.c4       { fill:rgb(255, 88, 88); fill-opacity:0.5; stroke-width:0; } \n");
	ख_लिखो(svgfile, "      rect.c5       { fill:rgb(255, 44, 44); fill-opacity:0.5; stroke-width:0; } \n");
	ख_लिखो(svgfile, "      rect.c6       { fill:rgb(255,  0,  0); fill-opacity:0.5; stroke-width:0; } \n");
	ख_लिखो(svgfile, "      line.pstate   { stroke:rgb(255,255,  0); stroke-opacity:0.8; stroke-width:2; } \n");

	ख_लिखो(svgfile, "    ]]>\n   </style>\n</defs>\n");
पूर्ण

अटल द्विगुन normalize_height(द्विगुन height)
अणु
	अगर (height < 0.25)
		वापस 0.25;
	अन्यथा अगर (height < 0.50)
		वापस 0.50;
	अन्यथा अगर (height < 0.75)
		वापस 0.75;
	अन्यथा
		वापस 0.100;
पूर्ण

व्योम svg_ubox(पूर्णांक Yslot, u64 start, u64 end, द्विगुन height, स्थिर अक्षर *type, पूर्णांक fd, पूर्णांक err, पूर्णांक merges)
अणु
	द्विगुन w = समय2pixels(end) - समय2pixels(start);
	height = normalize_height(height);

	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<g>\n");
	ख_लिखो(svgfile, "<title>fd=%d error=%d merges=%d</title>\n", fd, err, merges);
	ख_लिखो(svgfile, "<rect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" class=\"%s\"/>\n",
		समय2pixels(start),
		w,
		Yslot * SLOT_MULT,
		SLOT_HALF * height,
		type);
	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_lbox(पूर्णांक Yslot, u64 start, u64 end, द्विगुन height, स्थिर अक्षर *type, पूर्णांक fd, पूर्णांक err, पूर्णांक merges)
अणु
	द्विगुन w = समय2pixels(end) - समय2pixels(start);
	height = normalize_height(height);

	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<g>\n");
	ख_लिखो(svgfile, "<title>fd=%d error=%d merges=%d</title>\n", fd, err, merges);
	ख_लिखो(svgfile, "<rect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" class=\"%s\"/>\n",
		समय2pixels(start),
		w,
		Yslot * SLOT_MULT + SLOT_HEIGHT - SLOT_HALF * height,
		SLOT_HALF * height,
		type);
	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_fbox(पूर्णांक Yslot, u64 start, u64 end, द्विगुन height, स्थिर अक्षर *type, पूर्णांक fd, पूर्णांक err, पूर्णांक merges)
अणु
	द्विगुन w = समय2pixels(end) - समय2pixels(start);
	height = normalize_height(height);

	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<g>\n");
	ख_लिखो(svgfile, "<title>fd=%d error=%d merges=%d</title>\n", fd, err, merges);
	ख_लिखो(svgfile, "<rect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" class=\"%s\"/>\n",
		समय2pixels(start),
		w,
		Yslot * SLOT_MULT + SLOT_HEIGHT - SLOT_HEIGHT * height,
		SLOT_HEIGHT * height,
		type);
	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_box(पूर्णांक Yslot, u64 start, u64 end, स्थिर अक्षर *type)
अणु
	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<rect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" class=\"%s\"/>\n",
		समय2pixels(start), समय2pixels(end)-समय2pixels(start), Yslot * SLOT_MULT, SLOT_HEIGHT, type);
पूर्ण

अटल अक्षर *समय_प्रकारo_string(u64 duration);
व्योम svg_blocked(पूर्णांक Yslot, पूर्णांक cpu, u64 start, u64 end, स्थिर अक्षर *backtrace)
अणु
	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<g>\n");
	ख_लिखो(svgfile, "<title>#%d blocked %s</title>\n", cpu,
		समय_प्रकारo_string(end - start));
	अगर (backtrace)
		ख_लिखो(svgfile, "<desc>Blocked on:\n%s</desc>\n", backtrace);
	svg_box(Yslot, start, end, "blocked");
	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_running(पूर्णांक Yslot, पूर्णांक cpu, u64 start, u64 end, स्थिर अक्षर *backtrace)
अणु
	द्विगुन text_size;
	स्थिर अक्षर *type;

	अगर (!svgfile)
		वापस;

	अगर (svg_highlight && end - start > svg_highlight)
		type = "sample_hi";
	अन्यथा
		type = "sample";
	ख_लिखो(svgfile, "<g>\n");

	ख_लिखो(svgfile, "<title>#%d running %s</title>\n",
		cpu, समय_प्रकारo_string(end - start));
	अगर (backtrace)
		ख_लिखो(svgfile, "<desc>Switched because:\n%s</desc>\n", backtrace);
	ख_लिखो(svgfile, "<rect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" class=\"%s\"/>\n",
		समय2pixels(start), समय2pixels(end)-समय2pixels(start), Yslot * SLOT_MULT, SLOT_HEIGHT,
		type);

	text_size = (समय2pixels(end)-समय2pixels(start));
	अगर (cpu > 9)
		text_size = text_size/2;
	अगर (text_size > 1.25)
		text_size = 1.25;
	text_size = round_text_size(text_size);

	अगर (text_size > MIN_TEXT_SIZE)
		ख_लिखो(svgfile, "<text x=\"%.8f\" y=\"%.8f\" font-size=\"%.8fpt\">%i</text>\n",
			समय2pixels(start), Yslot *  SLOT_MULT + SLOT_HEIGHT - 1, text_size,  cpu + 1);

	ख_लिखो(svgfile, "</g>\n");
पूर्ण

अटल अक्षर *समय_प्रकारo_string(u64 duration)
अणु
	अटल अक्षर text[80];

	text[0] = 0;

	अगर (duration < NSEC_PER_USEC) /* less than 1 usec */
		वापस text;

	अगर (duration < NSEC_PER_MSEC) अणु /* less than 1 msec */
		प्र_लिखो(text, "%.1f us", duration / (द्विगुन)NSEC_PER_USEC);
		वापस text;
	पूर्ण
	प्र_लिखो(text, "%.1f ms", duration / (द्विगुन)NSEC_PER_MSEC);

	वापस text;
पूर्ण

व्योम svg_रुकोing(पूर्णांक Yslot, पूर्णांक cpu, u64 start, u64 end, स्थिर अक्षर *backtrace)
अणु
	अक्षर *text;
	स्थिर अक्षर *style;
	द्विगुन font_size;

	अगर (!svgfile)
		वापस;

	style = "waiting";

	अगर (end-start > 10 * NSEC_PER_MSEC) /* 10 msec */
		style = "WAITING";

	text = समय_प्रकारo_string(end-start);

	font_size = 1.0 * (समय2pixels(end)-समय2pixels(start));

	अगर (font_size > 3)
		font_size = 3;

	font_size = round_text_size(font_size);

	ख_लिखो(svgfile, "<g transform=\"translate(%.8f,%.8f)\">\n", समय2pixels(start), Yslot * SLOT_MULT);
	ख_लिखो(svgfile, "<title>#%d waiting %s</title>\n", cpu, समय_प्रकारo_string(end - start));
	अगर (backtrace)
		ख_लिखो(svgfile, "<desc>Waiting on:\n%s</desc>\n", backtrace);
	ख_लिखो(svgfile, "<rect x=\"0\" width=\"%.8f\" y=\"0\" height=\"%.1f\" class=\"%s\"/>\n",
		समय2pixels(end)-समय2pixels(start), SLOT_HEIGHT, style);
	अगर (font_size > MIN_TEXT_SIZE)
		ख_लिखो(svgfile, "<text transform=\"rotate(90)\" font-size=\"%.8fpt\"> %s</text>\n",
			font_size, text);
	ख_लिखो(svgfile, "</g>\n");
पूर्ण

अटल अक्षर *cpu_model(व्योम)
अणु
	अटल अक्षर cpu_m[255];
	अक्षर buf[256];
	खाता *file;

	cpu_m[0] = 0;
	/* CPU type */
	file = ख_खोलो("/proc/cpuinfo", "r");
	अगर (file) अणु
		जबतक (ख_माला_लो(buf, 255, file)) अणु
			अगर (म_माला(buf, "model name")) अणु
				strlcpy(cpu_m, &buf[13], 255);
				अवरोध;
			पूर्ण
		पूर्ण
		ख_बंद(file);
	पूर्ण

	/* CPU type */
	file = ख_खोलो("/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_frequencies", "r");
	अगर (file) अणु
		जबतक (ख_माला_लो(buf, 255, file)) अणु
			अचिन्हित पूर्णांक freq;
			freq = म_से_अदीर्घl(buf, शून्य, 10);
			अगर (freq > max_freq)
				max_freq = freq;
		पूर्ण
		ख_बंद(file);
	पूर्ण
	वापस cpu_m;
पूर्ण

व्योम svg_cpu_box(पूर्णांक cpu, u64 __max_freq, u64 __turbo_freq)
अणु
	अक्षर cpu_string[80];
	अगर (!svgfile)
		वापस;

	max_freq = __max_freq;
	turbo_frequency = __turbo_freq;

	ख_लिखो(svgfile, "<g>\n");

	ख_लिखो(svgfile, "<rect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" class=\"cpu\"/>\n",
		समय2pixels(first_समय),
		समय2pixels(last_समय)-समय2pixels(first_समय),
		cpu2y(cpu), SLOT_MULT+SLOT_HEIGHT);

	प्र_लिखो(cpu_string, "CPU %i", (पूर्णांक)cpu);
	ख_लिखो(svgfile, "<text x=\"%.8f\" y=\"%.8f\">%s</text>\n",
		10+समय2pixels(first_समय), cpu2y(cpu) + SLOT_HEIGHT/2, cpu_string);

	ख_लिखो(svgfile, "<text transform=\"translate(%.8f,%.8f)\" font-size=\"1.25pt\">%s</text>\n",
		10+समय2pixels(first_समय), cpu2y(cpu) + SLOT_MULT + SLOT_HEIGHT - 4, cpu_model());

	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_process(पूर्णांक cpu, u64 start, u64 end, पूर्णांक pid, स्थिर अक्षर *name, स्थिर अक्षर *backtrace)
अणु
	द्विगुन width;
	स्थिर अक्षर *type;

	अगर (!svgfile)
		वापस;

	अगर (svg_highlight && end - start >= svg_highlight)
		type = "sample_hi";
	अन्यथा अगर (svg_highlight_name && म_माला(name, svg_highlight_name))
		type = "sample_hi";
	अन्यथा
		type = "sample";

	ख_लिखो(svgfile, "<g transform=\"translate(%.8f,%.8f)\">\n", समय2pixels(start), cpu2y(cpu));
	ख_लिखो(svgfile, "<title>%d %s running %s</title>\n", pid, name, समय_प्रकारo_string(end - start));
	अगर (backtrace)
		ख_लिखो(svgfile, "<desc>Switched because:\n%s</desc>\n", backtrace);
	ख_लिखो(svgfile, "<rect x=\"0\" width=\"%.8f\" y=\"0\" height=\"%.1f\" class=\"%s\"/>\n",
		समय2pixels(end)-समय2pixels(start), SLOT_MULT+SLOT_HEIGHT, type);
	width = समय2pixels(end)-समय2pixels(start);
	अगर (width > 6)
		width = 6;

	width = round_text_size(width);

	अगर (width > MIN_TEXT_SIZE)
		ख_लिखो(svgfile, "<text transform=\"rotate(90)\" font-size=\"%.8fpt\">%s</text>\n",
			width, name);

	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_cstate(पूर्णांक cpu, u64 start, u64 end, पूर्णांक type)
अणु
	द्विगुन width;
	अक्षर style[128];

	अगर (!svgfile)
		वापस;


	ख_लिखो(svgfile, "<g>\n");

	अगर (type > 6)
		type = 6;
	प्र_लिखो(style, "c%i", type);

	ख_लिखो(svgfile, "<rect class=\"%s\" x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\"/>\n",
		style,
		समय2pixels(start), समय2pixels(end)-समय2pixels(start),
		cpu2y(cpu), SLOT_MULT+SLOT_HEIGHT);

	width = (समय2pixels(end)-समय2pixels(start))/2.0;
	अगर (width > 6)
		width = 6;

	width = round_text_size(width);

	अगर (width > MIN_TEXT_SIZE)
		ख_लिखो(svgfile, "<text x=\"%.8f\" y=\"%.8f\" font-size=\"%.8fpt\">C%i</text>\n",
			समय2pixels(start), cpu2y(cpu)+width, width, type);

	ख_लिखो(svgfile, "</g>\n");
पूर्ण

अटल अक्षर *HzToHuman(अचिन्हित दीर्घ hz)
अणु
	अटल अक्षर buffer[1024];
	अचिन्हित दीर्घ दीर्घ Hz;

	स_रखो(buffer, 0, 1024);

	Hz = hz;

	/* शेष: just put the Number in */
	प्र_लिखो(buffer, "%9lli", Hz);

	अगर (Hz > 1000)
		प्र_लिखो(buffer, " %6lli Mhz", (Hz+500)/1000);

	अगर (Hz > 1500000)
		प्र_लिखो(buffer, " %6.2f Ghz", (Hz+5000.0)/1000000);

	अगर (Hz == turbo_frequency)
		प्र_लिखो(buffer, "Turbo");

	वापस buffer;
पूर्ण

व्योम svg_pstate(पूर्णांक cpu, u64 start, u64 end, u64 freq)
अणु
	द्विगुन height = 0;

	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<g>\n");

	अगर (max_freq)
		height = freq * 1.0 / max_freq * (SLOT_HEIGHT + SLOT_MULT);
	height = 1 + cpu2y(cpu) + SLOT_MULT + SLOT_HEIGHT - height;
	ख_लिखो(svgfile, "<line x1=\"%.8f\" x2=\"%.8f\" y1=\"%.1f\" y2=\"%.1f\" class=\"pstate\"/>\n",
		समय2pixels(start), समय2pixels(end), height, height);
	ख_लिखो(svgfile, "<text x=\"%.8f\" y=\"%.8f\" font-size=\"0.25pt\">%s</text>\n",
		समय2pixels(start), height+0.9, HzToHuman(freq));

	ख_लिखो(svgfile, "</g>\n");
पूर्ण


व्योम svg_partial_wakeline(u64 start, पूर्णांक row1, अक्षर *desc1, पूर्णांक row2, अक्षर *desc2, स्थिर अक्षर *backtrace)
अणु
	द्विगुन height;

	अगर (!svgfile)
		वापस;


	ख_लिखो(svgfile, "<g>\n");

	ख_लिखो(svgfile, "<title>%s wakes up %s</title>\n",
		desc1 ? desc1 : "?",
		desc2 ? desc2 : "?");

	अगर (backtrace)
		ख_लिखो(svgfile, "<desc>%s</desc>\n", backtrace);

	अगर (row1 < row2) अणु
		अगर (row1) अणु
			ख_लिखो(svgfile, "<line x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" style=\"stroke:rgb(32,255,32);stroke-width:0.009\"/>\n",
				समय2pixels(start), row1 * SLOT_MULT + SLOT_HEIGHT,  समय2pixels(start), row1 * SLOT_MULT + SLOT_HEIGHT + SLOT_MULT/32);
			अगर (desc2)
				ख_लिखो(svgfile, "<g transform=\"translate(%.8f,%.8f)\"><text transform=\"rotate(90)\" font-size=\"0.02pt\">%s &gt;</text></g>\n",
					समय2pixels(start), row1 * SLOT_MULT + SLOT_HEIGHT + SLOT_HEIGHT/48, desc2);
		पूर्ण
		अगर (row2) अणु
			ख_लिखो(svgfile, "<line x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" style=\"stroke:rgb(32,255,32);stroke-width:0.009\"/>\n",
				समय2pixels(start), row2 * SLOT_MULT - SLOT_MULT/32,  समय2pixels(start), row2 * SLOT_MULT);
			अगर (desc1)
				ख_लिखो(svgfile, "<g transform=\"translate(%.8f,%.8f)\"><text transform=\"rotate(90)\" font-size=\"0.02pt\">%s &gt;</text></g>\n",
					समय2pixels(start), row2 * SLOT_MULT - SLOT_MULT/32, desc1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (row2) अणु
			ख_लिखो(svgfile, "<line x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" style=\"stroke:rgb(32,255,32);stroke-width:0.009\"/>\n",
				समय2pixels(start), row2 * SLOT_MULT + SLOT_HEIGHT,  समय2pixels(start), row2 * SLOT_MULT + SLOT_HEIGHT + SLOT_MULT/32);
			अगर (desc1)
				ख_लिखो(svgfile, "<g transform=\"translate(%.8f,%.8f)\"><text transform=\"rotate(90)\" font-size=\"0.02pt\">%s &lt;</text></g>\n",
					समय2pixels(start), row2 * SLOT_MULT + SLOT_HEIGHT + SLOT_MULT/48, desc1);
		पूर्ण
		अगर (row1) अणु
			ख_लिखो(svgfile, "<line x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" style=\"stroke:rgb(32,255,32);stroke-width:0.009\"/>\n",
				समय2pixels(start), row1 * SLOT_MULT - SLOT_MULT/32,  समय2pixels(start), row1 * SLOT_MULT);
			अगर (desc2)
				ख_लिखो(svgfile, "<g transform=\"translate(%.8f,%.8f)\"><text transform=\"rotate(90)\" font-size=\"0.02pt\">%s &lt;</text></g>\n",
					समय2pixels(start), row1 * SLOT_MULT - SLOT_HEIGHT/32, desc2);
		पूर्ण
	पूर्ण
	height = row1 * SLOT_MULT;
	अगर (row2 > row1)
		height += SLOT_HEIGHT;
	अगर (row1)
		ख_लिखो(svgfile, "<circle  cx=\"%.8f\" cy=\"%.2f\" r = \"0.01\"  style=\"fill:rgb(32,255,32)\"/>\n",
			समय2pixels(start), height);

	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_wakeline(u64 start, पूर्णांक row1, पूर्णांक row2, स्थिर अक्षर *backtrace)
अणु
	द्विगुन height;

	अगर (!svgfile)
		वापस;


	ख_लिखो(svgfile, "<g>\n");

	अगर (backtrace)
		ख_लिखो(svgfile, "<desc>%s</desc>\n", backtrace);

	अगर (row1 < row2)
		ख_लिखो(svgfile, "<line x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" style=\"stroke:rgb(32,255,32);stroke-width:0.009\"/>\n",
			समय2pixels(start), row1 * SLOT_MULT + SLOT_HEIGHT,  समय2pixels(start), row2 * SLOT_MULT);
	अन्यथा
		ख_लिखो(svgfile, "<line x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" style=\"stroke:rgb(32,255,32);stroke-width:0.009\"/>\n",
			समय2pixels(start), row2 * SLOT_MULT + SLOT_HEIGHT,  समय2pixels(start), row1 * SLOT_MULT);

	height = row1 * SLOT_MULT;
	अगर (row2 > row1)
		height += SLOT_HEIGHT;
	ख_लिखो(svgfile, "<circle  cx=\"%.8f\" cy=\"%.2f\" r = \"0.01\"  style=\"fill:rgb(32,255,32)\"/>\n",
			समय2pixels(start), height);

	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_पूर्णांकerrupt(u64 start, पूर्णांक row, स्थिर अक्षर *backtrace)
अणु
	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<g>\n");

	ख_लिखो(svgfile, "<title>Wakeup from interrupt</title>\n");

	अगर (backtrace)
		ख_लिखो(svgfile, "<desc>%s</desc>\n", backtrace);

	ख_लिखो(svgfile, "<circle  cx=\"%.8f\" cy=\"%.2f\" r = \"0.01\"  style=\"fill:rgb(255,128,128)\"/>\n",
			समय2pixels(start), row * SLOT_MULT);
	ख_लिखो(svgfile, "<circle  cx=\"%.8f\" cy=\"%.2f\" r = \"0.01\"  style=\"fill:rgb(255,128,128)\"/>\n",
			समय2pixels(start), row * SLOT_MULT + SLOT_HEIGHT);

	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_text(पूर्णांक Yslot, u64 start, स्थिर अक्षर *text)
अणु
	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<text x=\"%.8f\" y=\"%.8f\">%s</text>\n",
		समय2pixels(start), Yslot * SLOT_MULT+SLOT_HEIGHT/2, text);
पूर्ण

अटल व्योम svg_legenda_box(पूर्णांक X, स्थिर अक्षर *text, स्थिर अक्षर *style)
अणु
	द्विगुन boxsize;
	boxsize = SLOT_HEIGHT / 2;

	ख_लिखो(svgfile, "<rect x=\"%i\" width=\"%.8f\" y=\"0\" height=\"%.1f\" class=\"%s\"/>\n",
		X, boxsize, boxsize, style);
	ख_लिखो(svgfile, "<text transform=\"translate(%.8f, %.8f)\" font-size=\"%.8fpt\">%s</text>\n",
		X + boxsize + 5, boxsize, 0.8 * boxsize, text);
पूर्ण

व्योम svg_io_legenda(व्योम)
अणु
	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<g>\n");
	svg_legenda_box(0,	"Disk", "disk");
	svg_legenda_box(100,	"Network", "net");
	svg_legenda_box(200,	"Sync", "sync");
	svg_legenda_box(300,	"Poll", "poll");
	svg_legenda_box(400,	"Error", "error");
	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_legenda(व्योम)
अणु
	अगर (!svgfile)
		वापस;

	ख_लिखो(svgfile, "<g>\n");
	svg_legenda_box(0,	"Running", "sample");
	svg_legenda_box(100,	"Idle","c1");
	svg_legenda_box(200,	"Deeper Idle", "c3");
	svg_legenda_box(350,	"Deepest Idle", "c6");
	svg_legenda_box(550,	"Sleeping", "process2");
	svg_legenda_box(650,	"Waiting for cpu", "waiting");
	svg_legenda_box(800,	"Blocked on IO", "blocked");
	ख_लिखो(svgfile, "</g>\n");
पूर्ण

व्योम svg_समय_grid(द्विगुन min_thickness)
अणु
	u64 i;

	अगर (!svgfile)
		वापस;

	i = first_समय;
	जबतक (i < last_समय) अणु
		पूर्णांक color = 220;
		द्विगुन thickness = 0.075;
		अगर ((i % 100000000) == 0) अणु
			thickness = 0.5;
			color = 192;
		पूर्ण
		अगर ((i % 1000000000) == 0) अणु
			thickness = 2.0;
			color = 128;
		पूर्ण

		अगर (thickness >= min_thickness)
			ख_लिखो(svgfile, "<line x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%" PRIu64 "\" style=\"stroke:rgb(%i,%i,%i);stroke-width:%.3f\"/>\n",
				समय2pixels(i), SLOT_MULT/2, समय2pixels(i),
				total_height, color, color, color, thickness);

		i += 10000000;
	पूर्ण
पूर्ण

व्योम svg_बंद(व्योम)
अणु
	अगर (svgfile) अणु
		ख_लिखो(svgfile, "</svg>\n");
		ख_बंद(svgfile);
		svgfile = शून्य;
	पूर्ण
पूर्ण

#घोषणा cpumask_bits(maskp) ((maskp)->bits)
प्रकार काष्ठा अणु DECLARE_BITMAP(bits, MAX_NR_CPUS); पूर्ण cpumask_t;

काष्ठा topology अणु
	cpumask_t *sib_core;
	पूर्णांक sib_core_nr;
	cpumask_t *sib_thr;
	पूर्णांक sib_thr_nr;
पूर्ण;

अटल व्योम scan_thपढ़ो_topology(पूर्णांक *map, काष्ठा topology *t, पूर्णांक cpu,
				 पूर्णांक *pos, पूर्णांक nr_cpus)
अणु
	पूर्णांक i;
	पूर्णांक thr;

	क्रम (i = 0; i < t->sib_thr_nr; i++) अणु
		अगर (!test_bit(cpu, cpumask_bits(&t->sib_thr[i])))
			जारी;

		क्रम_each_set_bit(thr, cpumask_bits(&t->sib_thr[i]), nr_cpus)
			अगर (map[thr] == -1)
				map[thr] = (*pos)++;
	पूर्ण
पूर्ण

अटल व्योम scan_core_topology(पूर्णांक *map, काष्ठा topology *t, पूर्णांक nr_cpus)
अणु
	पूर्णांक pos = 0;
	पूर्णांक i;
	पूर्णांक cpu;

	क्रम (i = 0; i < t->sib_core_nr; i++)
		क्रम_each_set_bit(cpu, cpumask_bits(&t->sib_core[i]), nr_cpus)
			scan_thपढ़ो_topology(map, t, cpu, &pos, nr_cpus);
पूर्ण

अटल पूर्णांक str_to_biपंचांगap(अक्षर *s, cpumask_t *b, पूर्णांक nr_cpus)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा perf_cpu_map *m;
	पूर्णांक c;

	m = perf_cpu_map__new(s);
	अगर (!m)
		वापस -1;

	क्रम (i = 0; i < m->nr; i++) अणु
		c = m->map[i];
		अगर (c >= nr_cpus) अणु
			ret = -1;
			अवरोध;
		पूर्ण

		set_bit(c, cpumask_bits(b));
	पूर्ण

	perf_cpu_map__put(m);

	वापस ret;
पूर्ण

पूर्णांक svg_build_topology_map(काष्ठा perf_env *env)
अणु
	पूर्णांक i, nr_cpus;
	काष्ठा topology t;
	अक्षर *sib_core, *sib_thr;

	nr_cpus = min(env->nr_cpus_online, MAX_NR_CPUS);

	t.sib_core_nr = env->nr_sibling_cores;
	t.sib_thr_nr = env->nr_sibling_thपढ़ोs;
	t.sib_core = सुस्मृति(env->nr_sibling_cores, माप(cpumask_t));
	t.sib_thr = सुस्मृति(env->nr_sibling_thपढ़ोs, माप(cpumask_t));

	sib_core = env->sibling_cores;
	sib_thr = env->sibling_thपढ़ोs;

	अगर (!t.sib_core || !t.sib_thr) अणु
		ख_लिखो(मानक_त्रुटि, "topology: no memory\n");
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < env->nr_sibling_cores; i++) अणु
		अगर (str_to_biपंचांगap(sib_core, &t.sib_core[i], nr_cpus)) अणु
			ख_लिखो(मानक_त्रुटि, "topology: can't parse siblings map\n");
			जाओ निकास;
		पूर्ण

		sib_core += म_माप(sib_core) + 1;
	पूर्ण

	क्रम (i = 0; i < env->nr_sibling_thपढ़ोs; i++) अणु
		अगर (str_to_biपंचांगap(sib_thr, &t.sib_thr[i], nr_cpus)) अणु
			ख_लिखो(मानक_त्रुटि, "topology: can't parse siblings map\n");
			जाओ निकास;
		पूर्ण

		sib_thr += म_माप(sib_thr) + 1;
	पूर्ण

	topology_map = दो_स्मृति(माप(पूर्णांक) * nr_cpus);
	अगर (!topology_map) अणु
		ख_लिखो(मानक_त्रुटि, "topology: no memory\n");
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < nr_cpus; i++)
		topology_map[i] = -1;

	scan_core_topology(topology_map, &t, nr_cpus);

	वापस 0;

निकास:
	zमुक्त(&t.sib_core);
	zमुक्त(&t.sib_thr);

	वापस -1;
पूर्ण
