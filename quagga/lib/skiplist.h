/*
 * Skip List implementation based on code from William Pugh.
 * ftp://ftp.cs.umd.edu/pub/skipLists/
 */


#ifndef _ZEBRA_SKIPLIST_H
#define _ZEBRA_SKIPLIST_H

#define SKIPLIST_0TIMER_DEBUG 0

/* 
 * skiplistnodes must always contain data to be valid. Adding an
 * empty node to a list is invalid
 */
struct skiplistnode 
{
  void			*key;
  void			*value;
#if SKIPLIST_0TIMER_DEBUG
  int			flags;
#define SKIPLIST_NODE_FLAG_INSERTED 0x00000001
#endif

  struct skiplistnode	*forward[1];	/* variable sized */
};

struct skiplist 
{
  int			flags;

#define SKIPLIST_FLAG_ALLOW_DUPLICATES	0x00000001

  int			level;	/* max lvl (1 + current # of levels in list) */
  unsigned int		count;
  struct skiplistnode	*header;
  struct skiplistnode	*stats;
  struct skiplistnode	*last;	/* last real list item (NULL if empty list) */

  /*
   * Returns -1 if val1 < val2, 0 if equal?, 1 if val1 > val2.
   */
  int (*cmp) (void *val1, void *val2);

  /*
   * callback to free user-owned data when listnode is deleted.
   */
  void (*del) (void *val);
};


/* Prototypes. */
extern struct skiplist *
skiplist_new(
    int	flags,
    int (*cmp) (void *key1, void *key2),	/* NULL => default cmp */
    void (*del) (void *val));			/* NULL => no auto val free */

extern void
skiplist_free (struct skiplist *);

extern int
skiplist_insert(
    register struct skiplist	*l,
    register void		*key,
    register void		*value);

extern int
skiplist_delete(
    register struct skiplist	*l,
    register void		*key,
    register void		*value);

extern int
skiplist_search(
    register struct skiplist     *l,
    register void               *key,
    void                        **valuePointer);

extern int
skiplist_first_value(
    register struct skiplist	*l,			/* in */
    register void		*key,			/* in */
    void			**valuePointer,		/* in/out */
    void			**cursor);		/* out */

extern int
skiplist_next_value(
    register struct skiplist	*l,			/* in */
    register void		*key,			/* in */
    void			**valuePointer,		/* in/out */
    void			**cursor);		/* in/out */

extern int
skiplist_first(
    register struct skiplist     *l,
    void                        **keyPointer,
    void                        **valuePointer);

extern int
skiplist_last(
    register struct skiplist     *l,
    void                        **keyPointer,
    void                        **valuePointer);

extern int
skiplist_delete_first(
    register struct skiplist     *l);

extern int
skiplist_next(
    register struct skiplist	 *l,			/* in */
    void			**keyPointer,		/* out */
    void			**valuePointer,		/* out */
    void			**cursor);		/* in/out */

extern int
skiplist_empty(
    register struct skiplist	 *l);			/* in */

extern unsigned int
skiplist_count(
    register struct skiplist	 *l);			/* in */

#endif /* _ZEBRA_SKIPLIST_H */
