# Test Page

## Directories
<ul>
{% for page in site.pages %}
{%   if page.url.last == "/" %}
  <li><a href="{{ page.url }}">{{ page.title }}</a></li>
{%   endif %}
{% endfor %}
</ul>
