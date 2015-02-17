/*
** parsing.c for raytracer in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun May 30 17:02:04 2010 cailleux carole
** Last update Sun May 30 17:02:04 2010 cailleux carole
*/

#include <stdio.h>
#include <stdlib.h>
#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include <SDL/SDL.h>
#include "raytracer.h"

int		parsedoc(xmlDocPtr doc, xmlNodePtr cur, t_var *data)
{
  xmlChar	*key;

  cur = cur->xmlChildrenNode;
  create_link(data);
  while (cur)
    {
      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      if (!key)
	cur = cur->next;
      else if (f_special(data->list, (char *)key, (char *)cur->name))
	cur = cur->next;
      else if (f_int(data->list, (char *)key, (char *)cur->name))
	cur = cur->next;
      else if (f_float(data->list, (char *)key, (char *)cur->name))
	cur = cur->next;
      else
	{
	  xmlFree(key);
	  my_perror((char *)cur->name);
	  my_perror(": incorrect tag\n");
	  return (-1);
	}
      xmlFree(key);
    }
  return (0);
}

int		loop_parsing(xmlNodePtr root, xmlDocPtr doc, t_var *data)
{
  data->sizex = 1024;
  data->sizey = 768;
  data->thread = 8;
  data->antialiasing = 1;
  while (root)
    {
      if (xmlStrcmp(root->name, (const xmlChar *)"text")
	  && xmlStrcmp(root->name, (const xmlChar *)"comment"))
	{
	  if (!xmlStrcmp(root->name, (const xmlChar *)"object"))
	    {
	      if (parsedoc(doc, root, data) == -1)
		return (-1);
	    }
	  else if (root->name && f_attribute(root, doc, data))
	    {
	      my_perror((char *)root->name);
	      my_perror(": incorrect tag\n");
	      return (-1);
	    }
	}
      root = root->next;
    }
  return (0);
}

int		check_root_validity(xmlNodePtr root, xmlDocPtr doc)
{
  if (!root)
    {
      my_perror("raytracer: invalid XML document.\n");
      xmlFreeDoc(doc);
      return (-1);
    }
  else if (my_strcmp((char *)root->name, "scene"))
    {
      my_perror("Error: root node (");
      my_perror((char *)root->name);
      my_perror(") != \"scene\".\n");
      xmlFreeDoc(doc);
      return (-1);
    }
  return (0);
}

t_list		*parsing(char *path, t_var *data, int len)
{
  xmlDocPtr	doc;
  xmlNodePtr	root;

  doc = (!len) ? xmlParseFile(path) : xmlParseMemory(path, len);
  data->filename = (!len) ? remove_ext(path) : NULL;
  if (!doc)
    {
      my_perror("raytracer: invalid XML document.\n");
      xmlFreeDoc(doc);
      return (NULL);
    }
  root = xmlDocGetRootElement(doc);
  if (check_root_validity(root, doc) == -1)
    return (NULL);
  data->list = NULL;
  if (loop_parsing(root->xmlChildrenNode, doc, data) == -1)
    {
      xmlFreeDoc(doc);
      return (NULL);
    }
  xmlFreeDoc(doc);
  return (data->list);
}
