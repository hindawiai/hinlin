<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/util.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>

#समावेश "common.h"

/* Lock क्रम protecting policy. */
DEFINE_MUTEX(tomoyo_policy_lock);

/* Has /sbin/init started? */
bool tomoyo_policy_loaded;

/*
 * Mapping table from "enum tomoyo_mac_index" to
 * "enum tomoyo_mac_category_index".
 */
स्थिर u8 tomoyo_index2category[TOMOYO_MAX_MAC_INDEX] = अणु
	/* CONFIG::file group */
	[TOMOYO_MAC_खाता_EXECUTE]    = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_OPEN]       = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_CREATE]     = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_UNLINK]     = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_GETATTR]    = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_MKसूची]      = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_RMसूची]      = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_MKFIFO]     = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_MKSOCK]     = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_TRUNCATE]   = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_SYMLINK]    = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_MKBLOCK]    = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_MKCHAR]     = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_LINK]       = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_RENAME]     = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_CHMOD]      = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_CHOWN]      = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_CHGRP]      = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_IOCTL]      = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_CHROOT]     = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_MOUNT]      = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_UMOUNT]     = TOMOYO_MAC_CATEGORY_खाता,
	[TOMOYO_MAC_खाता_PIVOT_ROOT] = TOMOYO_MAC_CATEGORY_खाता,
	/* CONFIG::network group */
	[TOMOYO_MAC_NETWORK_INET_STREAM_BIND]       =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_INET_STREAM_LISTEN]     =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_INET_STREAM_CONNECT]    =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_INET_DGRAM_BIND]        =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_INET_DGRAM_SEND]        =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_INET_RAW_BIND]          =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_INET_RAW_SEND]          =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_UNIX_STREAM_BIND]       =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_UNIX_STREAM_LISTEN]     =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_UNIX_STREAM_CONNECT]    =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_UNIX_DGRAM_BIND]        =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_UNIX_DGRAM_SEND]        =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_BIND]    =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_LISTEN]  =
	TOMOYO_MAC_CATEGORY_NETWORK,
	[TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_CONNECT] =
	TOMOYO_MAC_CATEGORY_NETWORK,
	/* CONFIG::misc group */
	[TOMOYO_MAC_ENVIRON]         = TOMOYO_MAC_CATEGORY_MISC,
पूर्ण;

/**
 * tomoyo_convert_समय - Convert समय_प्रकार to YYYY/MM/DD hh/mm/ss.
 *
 * @समय:  Seconds since 1970/01/01 00:00:00.
 * @stamp: Poपूर्णांकer to "struct tomoyo_time".
 *
 * Returns nothing.
 */
व्योम tomoyo_convert_समय(समय64_t समय64, काष्ठा tomoyo_समय *stamp)
अणु
	काष्ठा पंचांग पंचांग;

	समय64_to_पंचांग(समय64, 0, &पंचांग);
	stamp->sec = पंचांग.पंचांग_sec;
	stamp->min = पंचांग.पंचांग_min;
	stamp->hour = पंचांग.पंचांग_hour;
	stamp->day = पंचांग.पंचांग_mday;
	stamp->month = पंचांग.पंचांग_mon + 1;
	stamp->year = पंचांग.पंचांग_year + 1900;
पूर्ण

/**
 * tomoyo_permstr - Find permission keywords.
 *
 * @string: String representation क्रम permissions in foo/bar/buz क्रमmat.
 * @keyword: Keyword to find from @string/
 *
 * Returns true अगर @keyword was found in @string, false otherwise.
 *
 * This function assumes that म_भेदन(w1, w2, म_माप(w1)) != 0 अगर w1 != w2.
 */
bool tomoyo_permstr(स्थिर अक्षर *string, स्थिर अक्षर *keyword)
अणु
	स्थिर अक्षर *cp = म_माला(string, keyword);

	अगर (cp)
		वापस cp == string || *(cp - 1) == '/';
	वापस false;
पूर्ण

/**
 * tomoyo_पढ़ो_token - Read a word from a line.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns a word on success, "" otherwise.
 *
 * To allow the caller to skip शून्य check, this function वापसs "" rather than
 * शून्य अगर there is no more words to पढ़ो.
 */
अक्षर *tomoyo_पढ़ो_token(काष्ठा tomoyo_acl_param *param)
अणु
	अक्षर *pos = param->data;
	अक्षर *del = म_अक्षर(pos, ' ');

	अगर (del)
		*del++ = '\0';
	अन्यथा
		del = pos + म_माप(pos);
	param->data = del;
	वापस pos;
पूर्ण

अटल bool tomoyo_correct_path2(स्थिर अक्षर *filename, स्थिर माप_प्रकार len);

/**
 * tomoyo_get_करोमुख्यname - Read a करोमुख्यname from a line.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns a करोमुख्यname on success, शून्य otherwise.
 */
स्थिर काष्ठा tomoyo_path_info *tomoyo_get_करोमुख्यname
(काष्ठा tomoyo_acl_param *param)
अणु
	अक्षर *start = param->data;
	अक्षर *pos = start;

	जबतक (*pos) अणु
		अगर (*pos++ != ' ' ||
		    tomoyo_correct_path2(pos, म_अक्षरnul(pos, ' ') - pos))
			जारी;
		*(pos - 1) = '\0';
		अवरोध;
	पूर्ण
	param->data = pos;
	अगर (tomoyo_correct_करोमुख्य(start))
		वापस tomoyo_get_name(start);
	वापस शून्य;
पूर्ण

/**
 * tomoyo_parse_uदीर्घ - Parse an "unsigned long" value.
 *
 * @result: Poपूर्णांकer to "unsigned long".
 * @str:    Poपूर्णांकer to string to parse.
 *
 * Returns one of values in "enum tomoyo_value_type".
 *
 * The @src is updated to poपूर्णांक the first अक्षरacter after the value
 * on success.
 */
u8 tomoyo_parse_uदीर्घ(अचिन्हित दीर्घ *result, अक्षर **str)
अणु
	स्थिर अक्षर *cp = *str;
	अक्षर *ep;
	पूर्णांक base = 10;

	अगर (*cp == '0') अणु
		अक्षर c = *(cp + 1);

		अगर (c == 'x' || c == 'X') अणु
			base = 16;
			cp += 2;
		पूर्ण अन्यथा अगर (c >= '0' && c <= '7') अणु
			base = 8;
			cp++;
		पूर्ण
	पूर्ण
	*result = simple_म_से_अदीर्घ(cp, &ep, base);
	अगर (cp == ep)
		वापस TOMOYO_VALUE_TYPE_INVALID;
	*str = ep;
	चयन (base) अणु
	हाल 16:
		वापस TOMOYO_VALUE_TYPE_HEXADECIMAL;
	हाल 8:
		वापस TOMOYO_VALUE_TYPE_OCTAL;
	शेष:
		वापस TOMOYO_VALUE_TYPE_DECIMAL;
	पूर्ण
पूर्ण

/**
 * tomoyo_prपूर्णांक_uदीर्घ - Prपूर्णांक an "unsigned long" value.
 *
 * @buffer:     Poपूर्णांकer to buffer.
 * @buffer_len: Size of @buffer.
 * @value:      An "unsigned long" value.
 * @type:       Type of @value.
 *
 * Returns nothing.
 */
व्योम tomoyo_prपूर्णांक_uदीर्घ(अक्षर *buffer, स्थिर पूर्णांक buffer_len,
			स्थिर अचिन्हित दीर्घ value, स्थिर u8 type)
अणु
	अगर (type == TOMOYO_VALUE_TYPE_DECIMAL)
		snम_लिखो(buffer, buffer_len, "%lu", value);
	अन्यथा अगर (type == TOMOYO_VALUE_TYPE_OCTAL)
		snम_लिखो(buffer, buffer_len, "0%lo", value);
	अन्यथा अगर (type == TOMOYO_VALUE_TYPE_HEXADECIMAL)
		snम_लिखो(buffer, buffer_len, "0x%lX", value);
	अन्यथा
		snम_लिखो(buffer, buffer_len, "type(%u)", type);
पूर्ण

/**
 * tomoyo_parse_name_जोड़ - Parse a tomoyo_name_जोड़.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 * @ptr:   Poपूर्णांकer to "struct tomoyo_name_union".
 *
 * Returns true on success, false otherwise.
 */
bool tomoyo_parse_name_जोड़(काष्ठा tomoyo_acl_param *param,
			     काष्ठा tomoyo_name_जोड़ *ptr)
अणु
	अक्षर *filename;

	अगर (param->data[0] == '@') अणु
		param->data++;
		ptr->group = tomoyo_get_group(param, TOMOYO_PATH_GROUP);
		वापस ptr->group != शून्य;
	पूर्ण
	filename = tomoyo_पढ़ो_token(param);
	अगर (!tomoyo_correct_word(filename))
		वापस false;
	ptr->filename = tomoyo_get_name(filename);
	वापस ptr->filename != शून्य;
पूर्ण

/**
 * tomoyo_parse_number_जोड़ - Parse a tomoyo_number_जोड़.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 * @ptr:   Poपूर्णांकer to "struct tomoyo_number_union".
 *
 * Returns true on success, false otherwise.
 */
bool tomoyo_parse_number_जोड़(काष्ठा tomoyo_acl_param *param,
			       काष्ठा tomoyo_number_जोड़ *ptr)
अणु
	अक्षर *data;
	u8 type;
	अचिन्हित दीर्घ v;

	स_रखो(ptr, 0, माप(*ptr));
	अगर (param->data[0] == '@') अणु
		param->data++;
		ptr->group = tomoyo_get_group(param, TOMOYO_NUMBER_GROUP);
		वापस ptr->group != शून्य;
	पूर्ण
	data = tomoyo_पढ़ो_token(param);
	type = tomoyo_parse_uदीर्घ(&v, &data);
	अगर (type == TOMOYO_VALUE_TYPE_INVALID)
		वापस false;
	ptr->values[0] = v;
	ptr->value_type[0] = type;
	अगर (!*data) अणु
		ptr->values[1] = v;
		ptr->value_type[1] = type;
		वापस true;
	पूर्ण
	अगर (*data++ != '-')
		वापस false;
	type = tomoyo_parse_uदीर्घ(&v, &data);
	अगर (type == TOMOYO_VALUE_TYPE_INVALID || *data || ptr->values[0] > v)
		वापस false;
	ptr->values[1] = v;
	ptr->value_type[1] = type;
	वापस true;
पूर्ण

/**
 * tomoyo_byte_range - Check whether the string is a \ooo style octal value.
 *
 * @str: Poपूर्णांकer to the string.
 *
 * Returns true अगर @str is a \ooo style octal value, false otherwise.
 *
 * TOMOYO uses \ooo style representation क्रम 0x01 - 0x20 and 0x7F - 0xFF.
 * This function verअगरies that \ooo is in valid range.
 */
अटल अंतरभूत bool tomoyo_byte_range(स्थिर अक्षर *str)
अणु
	वापस *str >= '0' && *str++ <= '3' &&
		*str >= '0' && *str++ <= '7' &&
		*str >= '0' && *str <= '7';
पूर्ण

/**
 * tomoyo_alphabet_अक्षर - Check whether the अक्षरacter is an alphabet.
 *
 * @c: The अक्षरacter to check.
 *
 * Returns true अगर @c is an alphabet अक्षरacter, false otherwise.
 */
अटल अंतरभूत bool tomoyo_alphabet_अक्षर(स्थिर अक्षर c)
अणु
	वापस (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
पूर्ण

/**
 * tomoyo_make_byte - Make byte value from three octal अक्षरacters.
 *
 * @c1: The first अक्षरacter.
 * @c2: The second अक्षरacter.
 * @c3: The third अक्षरacter.
 *
 * Returns byte value.
 */
अटल अंतरभूत u8 tomoyo_make_byte(स्थिर u8 c1, स्थिर u8 c2, स्थिर u8 c3)
अणु
	वापस ((c1 - '0') << 6) + ((c2 - '0') << 3) + (c3 - '0');
पूर्ण

/**
 * tomoyo_valid - Check whether the अक्षरacter is a valid अक्षर.
 *
 * @c: The अक्षरacter to check.
 *
 * Returns true अगर @c is a valid अक्षरacter, false otherwise.
 */
अटल अंतरभूत bool tomoyo_valid(स्थिर अचिन्हित अक्षर c)
अणु
	वापस c > ' ' && c < 127;
पूर्ण

/**
 * tomoyo_invalid - Check whether the अक्षरacter is an invalid अक्षर.
 *
 * @c: The अक्षरacter to check.
 *
 * Returns true अगर @c is an invalid अक्षरacter, false otherwise.
 */
अटल अंतरभूत bool tomoyo_invalid(स्थिर अचिन्हित अक्षर c)
अणु
	वापस c && (c <= ' ' || c >= 127);
पूर्ण

/**
 * tomoyo_str_starts - Check whether the given string starts with the given keyword.
 *
 * @src:  Poपूर्णांकer to poपूर्णांकer to the string.
 * @find: Poपूर्णांकer to the keyword.
 *
 * Returns true अगर @src starts with @find, false otherwise.
 *
 * The @src is updated to poपूर्णांक the first अक्षरacter after the @find
 * अगर @src starts with @find.
 */
bool tomoyo_str_starts(अक्षर **src, स्थिर अक्षर *find)
अणु
	स्थिर पूर्णांक len = म_माप(find);
	अक्षर *पंचांगp = *src;

	अगर (म_भेदन(पंचांगp, find, len))
		वापस false;
	पंचांगp += len;
	*src = पंचांगp;
	वापस true;
पूर्ण

/**
 * tomoyo_normalize_line - Format string.
 *
 * @buffer: The line to normalize.
 *
 * Leading and trailing whitespaces are हटाओd.
 * Multiple whitespaces are packed पूर्णांकo single space.
 *
 * Returns nothing.
 */
व्योम tomoyo_normalize_line(अचिन्हित अक्षर *buffer)
अणु
	अचिन्हित अक्षर *sp = buffer;
	अचिन्हित अक्षर *dp = buffer;
	bool first = true;

	जबतक (tomoyo_invalid(*sp))
		sp++;
	जबतक (*sp) अणु
		अगर (!first)
			*dp++ = ' ';
		first = false;
		जबतक (tomoyo_valid(*sp))
			*dp++ = *sp++;
		जबतक (tomoyo_invalid(*sp))
			sp++;
	पूर्ण
	*dp = '\0';
पूर्ण

/**
 * tomoyo_correct_word2 - Validate a string.
 *
 * @string: The string to check. Maybe non-'\0'-terminated.
 * @len:    Length of @string.
 *
 * Check whether the given string follows the naming rules.
 * Returns true अगर @string follows the naming rules, false otherwise.
 */
अटल bool tomoyo_correct_word2(स्थिर अक्षर *string, माप_प्रकार len)
अणु
	u8 recursion = 20;
	स्थिर अक्षर *स्थिर start = string;
	bool in_repetition = false;

	अगर (!len)
		जाओ out;
	जबतक (len--) अणु
		अचिन्हित अक्षर c = *string++;

		अगर (c == '\\') अणु
			अगर (!len--)
				जाओ out;
			c = *string++;
			अगर (c >= '0' && c <= '3') अणु
				अचिन्हित अक्षर d;
				अचिन्हित अक्षर e;

				अगर (!len-- || !len--)
					जाओ out;
				d = *string++;
				e = *string++;
				अगर (d < '0' || d > '7' || e < '0' || e > '7')
					जाओ out;
				c = tomoyo_make_byte(c, d, e);
				अगर (c <= ' ' || c >= 127)
					जारी;
				जाओ out;
			पूर्ण
			चयन (c) अणु
			हाल '\\':  /* "\\" */
			हाल '+':   /* "\+" */
			हाल '?':   /* "\?" */
			हाल 'x':   /* "\x" */
			हाल 'a':   /* "\a" */
			हाल '-':   /* "\-" */
				जारी;
			पूर्ण
			अगर (!recursion--)
				जाओ out;
			चयन (c) अणु
			हाल '*':   /* "\*" */
			हाल '@':   /* "\@" */
			हाल '$':   /* "\$" */
			हाल 'X':   /* "\X" */
			हाल 'A':   /* "\A" */
				जारी;
			हाल '{':   /* "/\{" */
				अगर (string - 3 < start || *(string - 3) != '/')
					जाओ out;
				in_repetition = true;
				जारी;
			हाल '}':   /* "\}/" */
				अगर (*string != '/')
					जाओ out;
				अगर (!in_repetition)
					जाओ out;
				in_repetition = false;
				जारी;
			पूर्ण
			जाओ out;
		पूर्ण अन्यथा अगर (in_repetition && c == '/') अणु
			जाओ out;
		पूर्ण अन्यथा अगर (c <= ' ' || c >= 127) अणु
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (in_repetition)
		जाओ out;
	वापस true;
 out:
	वापस false;
पूर्ण

/**
 * tomoyo_correct_word - Validate a string.
 *
 * @string: The string to check.
 *
 * Check whether the given string follows the naming rules.
 * Returns true अगर @string follows the naming rules, false otherwise.
 */
bool tomoyo_correct_word(स्थिर अक्षर *string)
अणु
	वापस tomoyo_correct_word2(string, म_माप(string));
पूर्ण

/**
 * tomoyo_correct_path2 - Check whether the given pathname follows the naming rules.
 *
 * @filename: The pathname to check.
 * @len:      Length of @filename.
 *
 * Returns true अगर @filename follows the naming rules, false otherwise.
 */
अटल bool tomoyo_correct_path2(स्थिर अक्षर *filename, स्थिर माप_प्रकार len)
अणु
	स्थिर अक्षर *cp1 = स_प्रथम(filename, '/', len);
	स्थिर अक्षर *cp2 = स_प्रथम(filename, '.', len);

	वापस cp1 && (!cp2 || (cp1 < cp2)) && tomoyo_correct_word2(filename, len);
पूर्ण

/**
 * tomoyo_correct_path - Validate a pathname.
 *
 * @filename: The pathname to check.
 *
 * Check whether the given pathname follows the naming rules.
 * Returns true अगर @filename follows the naming rules, false otherwise.
 */
bool tomoyo_correct_path(स्थिर अक्षर *filename)
अणु
	वापस tomoyo_correct_path2(filename, म_माप(filename));
पूर्ण

/**
 * tomoyo_correct_करोमुख्य - Check whether the given करोमुख्यname follows the naming rules.
 *
 * @करोमुख्यname: The करोमुख्यname to check.
 *
 * Returns true अगर @करोमुख्यname follows the naming rules, false otherwise.
 */
bool tomoyo_correct_करोमुख्य(स्थिर अचिन्हित अक्षर *करोमुख्यname)
अणु
	अगर (!करोमुख्यname || !tomoyo_करोमुख्य_def(करोमुख्यname))
		वापस false;
	करोमुख्यname = म_अक्षर(करोमुख्यname, ' ');
	अगर (!करोमुख्यname++)
		वापस true;
	जबतक (1) अणु
		स्थिर अचिन्हित अक्षर *cp = म_अक्षर(करोमुख्यname, ' ');

		अगर (!cp)
			अवरोध;
		अगर (!tomoyo_correct_path2(करोमुख्यname, cp - करोमुख्यname))
			वापस false;
		करोमुख्यname = cp + 1;
	पूर्ण
	वापस tomoyo_correct_path(करोमुख्यname);
पूर्ण

/**
 * tomoyo_करोमुख्य_def - Check whether the given token can be a करोमुख्यname.
 *
 * @buffer: The token to check.
 *
 * Returns true अगर @buffer possibly be a करोमुख्यname, false otherwise.
 */
bool tomoyo_करोमुख्य_def(स्थिर अचिन्हित अक्षर *buffer)
अणु
	स्थिर अचिन्हित अक्षर *cp;
	पूर्णांक len;

	अगर (*buffer != '<')
		वापस false;
	cp = म_अक्षर(buffer, ' ');
	अगर (!cp)
		len = म_माप(buffer);
	अन्यथा
		len = cp - buffer;
	अगर (buffer[len - 1] != '>' ||
	    !tomoyo_correct_word2(buffer + 1, len - 2))
		वापस false;
	वापस true;
पूर्ण

/**
 * tomoyo_find_करोमुख्य - Find a करोमुख्य by the given name.
 *
 * @करोमुख्यname: The करोमुख्यname to find.
 *
 * Returns poपूर्णांकer to "struct tomoyo_domain_info" अगर found, शून्य otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
काष्ठा tomoyo_करोमुख्य_info *tomoyo_find_करोमुख्य(स्थिर अक्षर *करोमुख्यname)
अणु
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य;
	काष्ठा tomoyo_path_info name;

	name.name = करोमुख्यname;
	tomoyo_fill_path_info(&name);
	list_क्रम_each_entry_rcu(करोमुख्य, &tomoyo_करोमुख्य_list, list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (!करोमुख्य->is_deleted &&
		    !tomoyo_pathcmp(&name, करोमुख्य->करोमुख्यname))
			वापस करोमुख्य;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * tomoyo_स्थिर_part_length - Evaluate the initial length without a pattern in a token.
 *
 * @filename: The string to evaluate.
 *
 * Returns the initial length without a pattern in @filename.
 */
अटल पूर्णांक tomoyo_स्थिर_part_length(स्थिर अक्षर *filename)
अणु
	अक्षर c;
	पूर्णांक len = 0;

	अगर (!filename)
		वापस 0;
	जबतक ((c = *filename++) != '\0') अणु
		अगर (c != '\\') अणु
			len++;
			जारी;
		पूर्ण
		c = *filename++;
		चयन (c) अणु
		हाल '\\':  /* "\\" */
			len += 2;
			जारी;
		हाल '0':   /* "\ooo" */
		हाल '1':
		हाल '2':
		हाल '3':
			c = *filename++;
			अगर (c < '0' || c > '7')
				अवरोध;
			c = *filename++;
			अगर (c < '0' || c > '7')
				अवरोध;
			len += 4;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस len;
पूर्ण

/**
 * tomoyo_fill_path_info - Fill in "struct tomoyo_path_info" members.
 *
 * @ptr: Poपूर्णांकer to "struct tomoyo_path_info" to fill in.
 *
 * The caller sets "struct tomoyo_path_info"->name.
 */
व्योम tomoyo_fill_path_info(काष्ठा tomoyo_path_info *ptr)
अणु
	स्थिर अक्षर *name = ptr->name;
	स्थिर पूर्णांक len = म_माप(name);

	ptr->स्थिर_len = tomoyo_स्थिर_part_length(name);
	ptr->is_dir = len && (name[len - 1] == '/');
	ptr->is_patterned = (ptr->स्थिर_len < len);
	ptr->hash = full_name_hash(शून्य, name, len);
पूर्ण

/**
 * tomoyo_file_matches_pattern2 - Pattern matching without '/' अक्षरacter and "\-" pattern.
 *
 * @filename:     The start of string to check.
 * @filename_end: The end of string to check.
 * @pattern:      The start of pattern to compare.
 * @pattern_end:  The end of pattern to compare.
 *
 * Returns true अगर @filename matches @pattern, false otherwise.
 */
अटल bool tomoyo_file_matches_pattern2(स्थिर अक्षर *filename,
					 स्थिर अक्षर *filename_end,
					 स्थिर अक्षर *pattern,
					 स्थिर अक्षर *pattern_end)
अणु
	जबतक (filename < filename_end && pattern < pattern_end) अणु
		अक्षर c;
		पूर्णांक i;
		पूर्णांक j;

		अगर (*pattern != '\\') अणु
			अगर (*filename++ != *pattern++)
				वापस false;
			जारी;
		पूर्ण
		c = *filename;
		pattern++;
		चयन (*pattern) अणु
		हाल '?':
			अगर (c == '/') अणु
				वापस false;
			पूर्ण अन्यथा अगर (c == '\\') अणु
				अगर (filename[1] == '\\')
					filename++;
				अन्यथा अगर (tomoyo_byte_range(filename + 1))
					filename += 3;
				अन्यथा
					वापस false;
			पूर्ण
			अवरोध;
		हाल '\\':
			अगर (c != '\\')
				वापस false;
			अगर (*++filename != '\\')
				वापस false;
			अवरोध;
		हाल '+':
			अगर (!है_अंक(c))
				वापस false;
			अवरोध;
		हाल 'x':
			अगर (!है_षष्ठादशक(c))
				वापस false;
			अवरोध;
		हाल 'a':
			अगर (!tomoyo_alphabet_अक्षर(c))
				वापस false;
			अवरोध;
		हाल '0':
		हाल '1':
		हाल '2':
		हाल '3':
			अगर (c == '\\' && tomoyo_byte_range(filename + 1)
			    && म_भेदन(filename + 1, pattern, 3) == 0) अणु
				filename += 3;
				pattern += 2;
				अवरोध;
			पूर्ण
			वापस false; /* Not matched. */
		हाल '*':
		हाल '@':
			क्रम (i = 0; i <= filename_end - filename; i++) अणु
				अगर (tomoyo_file_matches_pattern2(
						    filename + i, filename_end,
						    pattern + 1, pattern_end))
					वापस true;
				c = filename[i];
				अगर (c == '.' && *pattern == '@')
					अवरोध;
				अगर (c != '\\')
					जारी;
				अगर (filename[i + 1] == '\\')
					i++;
				अन्यथा अगर (tomoyo_byte_range(filename + i + 1))
					i += 3;
				अन्यथा
					अवरोध; /* Bad pattern. */
			पूर्ण
			वापस false; /* Not matched. */
		शेष:
			j = 0;
			c = *pattern;
			अगर (c == '$') अणु
				जबतक (है_अंक(filename[j]))
					j++;
			पूर्ण अन्यथा अगर (c == 'X') अणु
				जबतक (है_षष्ठादशक(filename[j]))
					j++;
			पूर्ण अन्यथा अगर (c == 'A') अणु
				जबतक (tomoyo_alphabet_अक्षर(filename[j]))
					j++;
			पूर्ण
			क्रम (i = 1; i <= j; i++) अणु
				अगर (tomoyo_file_matches_pattern2(
						    filename + i, filename_end,
						    pattern + 1, pattern_end))
					वापस true;
			पूर्ण
			वापस false; /* Not matched or bad pattern. */
		पूर्ण
		filename++;
		pattern++;
	पूर्ण
	जबतक (*pattern == '\\' &&
	       (*(pattern + 1) == '*' || *(pattern + 1) == '@'))
		pattern += 2;
	वापस filename == filename_end && pattern == pattern_end;
पूर्ण

/**
 * tomoyo_file_matches_pattern - Pattern matching without '/' अक्षरacter.
 *
 * @filename:     The start of string to check.
 * @filename_end: The end of string to check.
 * @pattern:      The start of pattern to compare.
 * @pattern_end:  The end of pattern to compare.
 *
 * Returns true अगर @filename matches @pattern, false otherwise.
 */
अटल bool tomoyo_file_matches_pattern(स्थिर अक्षर *filename,
					स्थिर अक्षर *filename_end,
					स्थिर अक्षर *pattern,
					स्थिर अक्षर *pattern_end)
अणु
	स्थिर अक्षर *pattern_start = pattern;
	bool first = true;
	bool result;

	जबतक (pattern < pattern_end - 1) अणु
		/* Split at "\-" pattern. */
		अगर (*pattern++ != '\\' || *pattern++ != '-')
			जारी;
		result = tomoyo_file_matches_pattern2(filename,
						      filename_end,
						      pattern_start,
						      pattern - 2);
		अगर (first)
			result = !result;
		अगर (result)
			वापस false;
		first = false;
		pattern_start = pattern;
	पूर्ण
	result = tomoyo_file_matches_pattern2(filename, filename_end,
					      pattern_start, pattern_end);
	वापस first ? result : !result;
पूर्ण

/**
 * tomoyo_path_matches_pattern2 - Do pathname pattern matching.
 *
 * @f: The start of string to check.
 * @p: The start of pattern to compare.
 *
 * Returns true अगर @f matches @p, false otherwise.
 */
अटल bool tomoyo_path_matches_pattern2(स्थिर अक्षर *f, स्थिर अक्षर *p)
अणु
	स्थिर अक्षर *f_delimiter;
	स्थिर अक्षर *p_delimiter;

	जबतक (*f && *p) अणु
		f_delimiter = म_अक्षर(f, '/');
		अगर (!f_delimiter)
			f_delimiter = f + म_माप(f);
		p_delimiter = म_अक्षर(p, '/');
		अगर (!p_delimiter)
			p_delimiter = p + म_माप(p);
		अगर (*p == '\\' && *(p + 1) == '{')
			जाओ recursive;
		अगर (!tomoyo_file_matches_pattern(f, f_delimiter, p,
						 p_delimiter))
			वापस false;
		f = f_delimiter;
		अगर (*f)
			f++;
		p = p_delimiter;
		अगर (*p)
			p++;
	पूर्ण
	/* Ignore trailing "\*" and "\@" in @pattern. */
	जबतक (*p == '\\' &&
	       (*(p + 1) == '*' || *(p + 1) == '@'))
		p += 2;
	वापस !*f && !*p;
 recursive:
	/*
	 * The "\{" pattern is permitted only after '/' अक्षरacter.
	 * This guarantees that below "*(p - 1)" is safe.
	 * Also, the "\}" pattern is permitted only beक्रमe '/' अक्षरacter
	 * so that "\{" + "\}" pair will not अवरोध the "\-" चालक.
	 */
	अगर (*(p - 1) != '/' || p_delimiter <= p + 3 || *p_delimiter != '/' ||
	    *(p_delimiter - 1) != '}' || *(p_delimiter - 2) != '\\')
		वापस false; /* Bad pattern. */
	करो अणु
		/* Compare current component with pattern. */
		अगर (!tomoyo_file_matches_pattern(f, f_delimiter, p + 2,
						 p_delimiter - 2))
			अवरोध;
		/* Proceed to next component. */
		f = f_delimiter;
		अगर (!*f)
			अवरोध;
		f++;
		/* Continue comparison. */
		अगर (tomoyo_path_matches_pattern2(f, p_delimiter + 1))
			वापस true;
		f_delimiter = म_अक्षर(f, '/');
	पूर्ण जबतक (f_delimiter);
	वापस false; /* Not matched. */
पूर्ण

/**
 * tomoyo_path_matches_pattern - Check whether the given filename matches the given pattern.
 *
 * @filename: The filename to check.
 * @pattern:  The pattern to compare.
 *
 * Returns true अगर matches, false otherwise.
 *
 * The following patterns are available.
 *   \\     \ itself.
 *   \ooo   Octal representation of a byte.
 *   \*     Zero or more repetitions of अक्षरacters other than '/'.
 *   \@     Zero or more repetitions of अक्षरacters other than '/' or '.'.
 *   \?     1 byte अक्षरacter other than '/'.
 *   \$     One or more repetitions of decimal digits.
 *   \+     1 decimal digit.
 *   \X     One or more repetitions of hexadecimal digits.
 *   \ष     1 hexadecimal digit.
 *   \A     One or more repetitions of alphabet अक्षरacters.
 *   \च     1 alphabet अक्षरacter.
 *
 *   \-     Subtraction चालक.
 *
 *   /\अणुdir\पूर्ण/   '/' + 'One or more repetitions of dir/' (e.g. /dir/ /dir/dir/
 *               /dir/dir/dir/ ).
 */
bool tomoyo_path_matches_pattern(स्थिर काष्ठा tomoyo_path_info *filename,
				 स्थिर काष्ठा tomoyo_path_info *pattern)
अणु
	स्थिर अक्षर *f = filename->name;
	स्थिर अक्षर *p = pattern->name;
	स्थिर पूर्णांक len = pattern->स्थिर_len;

	/* If @pattern करोesn't contain pattern, I can use म_भेद(). */
	अगर (!pattern->is_patterned)
		वापस !tomoyo_pathcmp(filename, pattern);
	/* Don't compare directory and non-directory. */
	अगर (filename->is_dir != pattern->is_dir)
		वापस false;
	/* Compare the initial length without patterns. */
	अगर (म_भेदन(f, p, len))
		वापस false;
	f += len;
	p += len;
	वापस tomoyo_path_matches_pattern2(f, p);
पूर्ण

/**
 * tomoyo_get_exe - Get tomoyo_realpath() of current process.
 *
 * Returns the tomoyo_realpath() of current process on success, शून्य otherwise.
 *
 * This function uses kzalloc(), so the caller must call kमुक्त()
 * अगर this function didn't वापस शून्य.
 */
स्थिर अक्षर *tomoyo_get_exe(व्योम)
अणु
	काष्ठा file *exe_file;
	स्थिर अक्षर *cp;
	काष्ठा mm_काष्ठा *mm = current->mm;

	अगर (!mm)
		वापस शून्य;
	exe_file = get_mm_exe_file(mm);
	अगर (!exe_file)
		वापस शून्य;

	cp = tomoyo_realpath_from_path(&exe_file->f_path);
	fput(exe_file);
	वापस cp;
पूर्ण

/**
 * tomoyo_get_mode - Get MAC mode.
 *
 * @ns:      Poपूर्णांकer to "struct tomoyo_policy_namespace".
 * @profile: Profile number.
 * @index:   Index number of functionality.
 *
 * Returns mode.
 */
पूर्णांक tomoyo_get_mode(स्थिर काष्ठा tomoyo_policy_namespace *ns, स्थिर u8 profile,
		    स्थिर u8 index)
अणु
	u8 mode;
	काष्ठा tomoyo_profile *p;

	अगर (!tomoyo_policy_loaded)
		वापस TOMOYO_CONFIG_DISABLED;
	p = tomoyo_profile(ns, profile);
	mode = p->config[index];
	अगर (mode == TOMOYO_CONFIG_USE_DEFAULT)
		mode = p->config[tomoyo_index2category[index]
				 + TOMOYO_MAX_MAC_INDEX];
	अगर (mode == TOMOYO_CONFIG_USE_DEFAULT)
		mode = p->शेष_config;
	वापस mode & 3;
पूर्ण

/**
 * tomoyo_init_request_info - Initialize "struct tomoyo_request_info" members.
 *
 * @r:      Poपूर्णांकer to "struct tomoyo_request_info" to initialize.
 * @करोमुख्य: Poपूर्णांकer to "struct tomoyo_domain_info". शून्य क्रम tomoyo_करोमुख्य().
 * @index:  Index number of functionality.
 *
 * Returns mode.
 */
पूर्णांक tomoyo_init_request_info(काष्ठा tomoyo_request_info *r,
			     काष्ठा tomoyo_करोमुख्य_info *करोमुख्य, स्थिर u8 index)
अणु
	u8 profile;

	स_रखो(r, 0, माप(*r));
	अगर (!करोमुख्य)
		करोमुख्य = tomoyo_करोमुख्य();
	r->करोमुख्य = करोमुख्य;
	profile = करोमुख्य->profile;
	r->profile = profile;
	r->type = index;
	r->mode = tomoyo_get_mode(करोमुख्य->ns, profile, index);
	वापस r->mode;
पूर्ण

/**
 * tomoyo_करोमुख्य_quota_is_ok - Check क्रम करोमुख्य's quota.
 *
 * @r: Poपूर्णांकer to "struct tomoyo_request_info".
 *
 * Returns true अगर the करोमुख्य is not exceeded quota, false otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
bool tomoyo_करोमुख्य_quota_is_ok(काष्ठा tomoyo_request_info *r)
अणु
	अचिन्हित पूर्णांक count = 0;
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य = r->करोमुख्य;
	काष्ठा tomoyo_acl_info *ptr;

	अगर (r->mode != TOMOYO_CONFIG_LEARNING)
		वापस false;
	अगर (!करोमुख्य)
		वापस true;
	list_क्रम_each_entry_rcu(ptr, &करोमुख्य->acl_info_list, list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		u16 perm;
		u8 i;

		अगर (ptr->is_deleted)
			जारी;
		/*
		 * Reading perm biपंचांगap might race with tomoyo_merge_*() because
		 * caller करोes not hold tomoyo_policy_lock mutex. But exceeding
		 * max_learning_entry parameter by a few entries करोes not harm.
		 */
		चयन (ptr->type) अणु
		हाल TOMOYO_TYPE_PATH_ACL:
			data_race(perm = container_of(ptr, काष्ठा tomoyo_path_acl, head)->perm);
			अवरोध;
		हाल TOMOYO_TYPE_PATH2_ACL:
			data_race(perm = container_of(ptr, काष्ठा tomoyo_path2_acl, head)->perm);
			अवरोध;
		हाल TOMOYO_TYPE_PATH_NUMBER_ACL:
			data_race(perm = container_of(ptr, काष्ठा tomoyo_path_number_acl, head)
				  ->perm);
			अवरोध;
		हाल TOMOYO_TYPE_MKDEV_ACL:
			data_race(perm = container_of(ptr, काष्ठा tomoyo_mkdev_acl, head)->perm);
			अवरोध;
		हाल TOMOYO_TYPE_INET_ACL:
			data_race(perm = container_of(ptr, काष्ठा tomoyo_inet_acl, head)->perm);
			अवरोध;
		हाल TOMOYO_TYPE_UNIX_ACL:
			data_race(perm = container_of(ptr, काष्ठा tomoyo_unix_acl, head)->perm);
			अवरोध;
		हाल TOMOYO_TYPE_MANUAL_TASK_ACL:
			perm = 0;
			अवरोध;
		शेष:
			perm = 1;
		पूर्ण
		क्रम (i = 0; i < 16; i++)
			अगर (perm & (1 << i))
				count++;
	पूर्ण
	अगर (count < tomoyo_profile(करोमुख्य->ns, करोमुख्य->profile)->
	    pref[TOMOYO_PREF_MAX_LEARNING_ENTRY])
		वापस true;
	अगर (!करोमुख्य->flags[TOMOYO_DIF_QUOTA_WARNED]) अणु
		करोमुख्य->flags[TOMOYO_DIF_QUOTA_WARNED] = true;
		/* r->granted = false; */
		tomoyo_ग_लिखो_log(r, "%s", tomoyo_dअगर[TOMOYO_DIF_QUOTA_WARNED]);
#अगर_अघोषित CONFIG_SECURITY_TOMOYO_INSECURE_BUILTIN_SETTING
		pr_warn("WARNING: Domain '%s' has too many ACLs to hold. Stopped learning mode.\n",
			करोमुख्य->करोमुख्यname->name);
#पूर्ण_अगर
	पूर्ण
	वापस false;
पूर्ण
