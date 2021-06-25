<शैली गुरु>
#समावेश <मानकपन.स>
#समावेश <सीमा.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश "spark.h"
#समावेश "stat.h"

#घोषणा SPARK_SHIFT 8

/* Prपूर्णांक spark lines on outf क्रम numval values in val. */
पूर्णांक prपूर्णांक_spark(अक्षर *bf, पूर्णांक size, अचिन्हित दीर्घ *val, पूर्णांक numval)
अणु
	अटल स्थिर अक्षर *ticks[NUM_SPARKS] = अणु
		"ै",  "ै", "ै", "ै", "ै", "ै", "ै", "ै"
	पूर्ण;
	पूर्णांक i, prपूर्णांकed = 0;
	अचिन्हित दीर्घ min = अच_दीर्घ_उच्च, max = 0, f;

	क्रम (i = 0; i < numval; i++) अणु
		अगर (val[i] < min)
			min = val[i];
		अगर (val[i] > max)
			max = val[i];
	पूर्ण
	f = ((max - min) << SPARK_SHIFT) / (NUM_SPARKS - 1);
	अगर (f < 1)
		f = 1;
	क्रम (i = 0; i < numval; i++) अणु
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s",
				     ticks[((val[i] - min) << SPARK_SHIFT) / f]);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण
