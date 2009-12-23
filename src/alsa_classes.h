/* alsa_classes.h */
/* This code is part of the Public Domain. */

#ifndef __ALSA_CLASSES__
#define __ALSA_CLASSES__


//This stores data about an element (e.g. Front Volume, Front Switch, etc.)
//and provides get() and set() functions to deal with its values.  Numbers are
//This stores data about an element (e.g. Front Volume, Front Switch, etc.)
//and provides get() and set() functions to deal with its values.  Numbers are
//scaled to be in a 0-100 range.
class Element {
	public:
		Element(char *_card, int _numid, const char *_name);
		char *card;
		int numid;
		int index;
		char name[80];
		char short_name[80];
		char type[16];
		int values;
		int switch_id;
		bool associated;
		
		unsigned int number_of_enums;
		char **enums;
		
		int get();
		int get(int n);
		void sget(char *ret);
		
		int set(int num);
		int set(int num, int n);
		void set_lr(int lvol, int rvol);
		
		static float get_callback(void *obj);
		static float get_callback(void *obj, int n);
		static float set_callback(void *obj, float num);
		static float set_callback(void *obj, float num, int n);
		
		void print();
		
		
	private:
		int min;
		int max;
		int scale_out(int num);
		int scale_in(int num);
		int _get(int n);
		int _set(int num, int n);
};


//This stores a list of all Elements that are availible on a card
class ElementList {
	public:
		ElementList(char *_card);
		
		char card[8];
		
		//elems holds the array of all elements
		int num_elems;
		Element *elems;
		
		//items is an ordered list of the specific elements desired
		int num_items;
		Element **items;
		
		//returns a list of all elements in this list
		int list_my_names(char list[][80]);
		//returns a list of all element names
		int list_all_names(char list[][80]);
		//returns a list of all elements not in this list
		int list_other_names(char list[][80]);
		//populates the items array by sorting elems and skipping switches that are associated with an element
		void populate_items();
		//rearranges the items array so the current indexes are reordered to match 'order'
		void reorder_items(int *order, int n);
};

//replaces any instance of 'oldstr' found in dest with newstr, and returns true if dest was modified
bool strrep(char *dest, char *oldstr, char *newstr);


#endif
