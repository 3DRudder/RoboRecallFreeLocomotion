# List

{% for repository in site.github.public_repositories %}
### [{{ repository.name }}]({% if repository.has_pages %}{{ repository.pages_hostname }}/{{ repository.name }}{% else %}{{ repository.html_url }}{% endif %}) ({{ repository.size }} Ko)
* {{ repository.description }} [[Download release]({{ repository.html_url }}/releases/)]
{% endfor %}
